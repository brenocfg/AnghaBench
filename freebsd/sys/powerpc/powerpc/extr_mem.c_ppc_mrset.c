#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mem_range_softc {int mr_ndesc; struct mem_range_desc* mr_desc; } ;
struct mem_range_desc {int /*<<< orphan*/  mr_len; int /*<<< orphan*/  mr_base; int /*<<< orphan*/  mr_flags; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MDF_ACTIVE ; 
#define  MEMRANGE_SET_REMOVE 129 
#define  MEMRANGE_SET_UPDATE 128 
 int /*<<< orphan*/  bzero (struct mem_range_desc*,int) ; 

__attribute__((used)) static int
ppc_mrset(struct mem_range_softc *sc, struct mem_range_desc *desc, int *arg)
{
	int i;

	switch(*arg) {
	case MEMRANGE_SET_UPDATE:
		for (i = 0; i < sc->mr_ndesc; i++) {
			if (!sc->mr_desc[i].mr_len) {
				sc->mr_desc[i] = *desc;
				sc->mr_desc[i].mr_flags |= MDF_ACTIVE;
				return (0);
			}
			if (sc->mr_desc[i].mr_base == desc->mr_base &&
			    sc->mr_desc[i].mr_len == desc->mr_len)
				return (EEXIST);
		}
		return (ENOSPC);
	case MEMRANGE_SET_REMOVE:
		for (i = 0; i < sc->mr_ndesc; i++)
			if (sc->mr_desc[i].mr_base == desc->mr_base &&
			    sc->mr_desc[i].mr_len == desc->mr_len) {
				bzero(&sc->mr_desc[i], sizeof(sc->mr_desc[i]));
				return (0);
			}
		return (ENOENT);
	default:
		return (EOPNOTSUPP);
	}

	return (0);
}