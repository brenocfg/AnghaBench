#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct bcma_sport_list {int dummy; } ;
struct bcma_sport {int m_rid; int /*<<< orphan*/  sp_num_maps; struct bcma_sport_list sp_maps; int /*<<< orphan*/  m_size; int /*<<< orphan*/  m_base; scalar_t__ m_region_num; } ;
struct bcma_map {int m_rid; int /*<<< orphan*/  sp_num_maps; struct bcma_sport_list sp_maps; int /*<<< orphan*/  m_size; int /*<<< orphan*/  m_base; scalar_t__ m_region_num; } ;
struct bcma_erom_sport_region {scalar_t__ region_type; int /*<<< orphan*/  size; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  region_port; } ;
struct bcma_erom {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  core_idx; } ;
struct bcma_corecfg {TYPE_1__ core_info; } ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bhnd_port_type ;
typedef  scalar_t__ bcma_rmid_t ;
typedef  int /*<<< orphan*/  bcma_pid_t ;

/* Variables and functions */
 scalar_t__ BCMA_RMID_MAX ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EROM_LOG (struct bcma_erom*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct bcma_sport_list*,struct bcma_sport*,int /*<<< orphan*/ ) ; 
 struct bcma_sport* bcma_alloc_sport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcma_sport_list* bcma_corecfg_get_port_list (struct bcma_corecfg*,int /*<<< orphan*/ ) ; 
 int bcma_erom_parse_sport_region (struct bcma_erom*,struct bcma_erom_sport_region*) ; 
 int bcma_erom_region_to_port_type (struct bcma_erom*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcma_erom_seek (struct bcma_erom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_erom_tell (struct bcma_erom*) ; 
 int /*<<< orphan*/  bcma_free_sport (struct bcma_sport*) ; 
 int /*<<< orphan*/  bhnd_port_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_link ; 
 struct bcma_sport* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp_link ; 

__attribute__((used)) static int 
bcma_erom_corecfg_fill_port_regions(struct bcma_erom *erom,
    struct bcma_corecfg *corecfg, bcma_pid_t port_num,
    uint8_t region_type)
{
	struct bcma_sport	*sport;
	struct bcma_sport_list	*sports;
	bus_size_t		 entry_offset;
	int			 error;
	bhnd_port_type		 port_type;

	error = 0;

	/* Determine the port type for this region type. */
	error = bcma_erom_region_to_port_type(erom, region_type, &port_type);
	if (error)
		return (error);

	/* Fetch the list to be populated */
	sports = bcma_corecfg_get_port_list(corecfg, port_type);
	
	/* Allocate a new port descriptor */
	sport = bcma_alloc_sport(port_num, port_type);
	if (sport == NULL)
		return (ENOMEM);

	/* Read all address regions defined for this port */
	for (bcma_rmid_t region_num = 0;; region_num++) {
		struct bcma_map			*map;
		struct bcma_erom_sport_region	 spr;

		/* No valid port definition should come anywhere near
		 * BCMA_RMID_MAX. */
		if (region_num == BCMA_RMID_MAX) {
			EROM_LOG(erom, "core%u %s%u: region count reached "
			    "upper limit of %u\n",
			    corecfg->core_info.core_idx,
			    bhnd_port_type_name(port_type),
			    port_num, BCMA_RMID_MAX);

			error = EINVAL;
			goto cleanup;
		}

		/* Parse the next region entry. */
		entry_offset = bcma_erom_tell(erom);
		error = bcma_erom_parse_sport_region(erom, &spr);
		if (error && error != ENOENT) {
			EROM_LOG(erom, "core%u %s%u.%u: invalid slave port "
			    "address region\n",
			    corecfg->core_info.core_idx,
			    bhnd_port_type_name(port_type),
			    port_num, region_num);
			goto cleanup;
		}

		/* ENOENT signals no further region entries */
		if (error == ENOENT) {
			/* No further entries */
			error = 0;
			break;
		} 
		
		/* A region or type mismatch also signals no further region
		 * entries */
		if (spr.region_port != port_num ||
		    spr.region_type != region_type)
		{
			/* We don't want to consume this entry */
			bcma_erom_seek(erom, entry_offset);

			error = 0;
			goto cleanup;
		}

		/*
		 * Create the map entry. 
		 */
		map = malloc(sizeof(struct bcma_map), M_BHND, M_NOWAIT);
		if (map == NULL) {
			error = ENOMEM;
			goto cleanup;
		}

		map->m_region_num = region_num;
		map->m_base = spr.base_addr;
		map->m_size = spr.size;
		map->m_rid = -1;

		/* Add the region map to the port */
		STAILQ_INSERT_TAIL(&sport->sp_maps, map, m_link);
		sport->sp_num_maps++;
	}

cleanup:
	/* Append the new port descriptor on success, or deallocate the
	 * partially parsed descriptor on failure. */
	if (error == 0) {
		STAILQ_INSERT_TAIL(sports, sport, sp_link);
	} else if (sport != NULL) {
		bcma_free_sport(sport);
	}

	return error;
}