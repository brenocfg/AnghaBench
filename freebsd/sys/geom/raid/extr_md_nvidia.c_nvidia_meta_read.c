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
typedef  scalar_t__ uint32_t ;
struct nvidia_raid_conf {int config_size; int state; int type; int /*<<< orphan*/  nvidia_id; } ;
struct g_provider {int sectorsize; int /*<<< orphan*/  name; scalar_t__ mediasize; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG (int,char*,int,...) ; 
 int /*<<< orphan*/  M_MD_NVIDIA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NVIDIA_MAGIC ; 
 int NVIDIA_S_IDLE ; 
 int NVIDIA_S_INIT ; 
 int NVIDIA_S_REBUILD ; 
 int NVIDIA_S_SYNC ; 
 int NVIDIA_T_CONCAT ; 
 int NVIDIA_T_RAID0 ; 
 int NVIDIA_T_RAID01 ; 
 int NVIDIA_T_RAID1 ; 
 int NVIDIA_T_RAID3 ; 
 int NVIDIA_T_RAID5 ; 
 int NVIDIA_T_RAID5_SYM ; 
 int /*<<< orphan*/  free (struct nvidia_raid_conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_read_data (struct g_consumer*,scalar_t__,int,int*) ; 
 struct nvidia_raid_conf* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct nvidia_raid_conf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nvidia_raid_conf *
nvidia_meta_read(struct g_consumer *cp)
{
	struct g_provider *pp;
	struct nvidia_raid_conf *meta;
	char *buf;
	int error, i;
	uint32_t checksum, *ptr;

	pp = cp->provider;

	/* Read the anchor sector. */
	buf = g_read_data(cp,
	    pp->mediasize - 2 * pp->sectorsize, pp->sectorsize, &error);
	if (buf == NULL) {
		G_RAID_DEBUG(1, "Cannot read metadata from %s (error=%d).",
		    pp->name, error);
		return (NULL);
	}
	meta = (struct nvidia_raid_conf *)buf;

	/* Check if this is an NVIDIA RAID struct */
	if (strncmp(meta->nvidia_id, NVIDIA_MAGIC, strlen(NVIDIA_MAGIC))) {
		G_RAID_DEBUG(1, "NVIDIA signature check failed on %s", pp->name);
		g_free(buf);
		return (NULL);
	}
	if (meta->config_size > 128 ||
	    meta->config_size < 30) {
		G_RAID_DEBUG(1, "NVIDIA metadata size looks wrong: %d",
		    meta->config_size);
		g_free(buf);
		return (NULL);
	}
	meta = malloc(sizeof(*meta), M_MD_NVIDIA, M_WAITOK);
	memcpy(meta, buf, min(sizeof(*meta), pp->sectorsize));
	g_free(buf);

	/* Check metadata checksum. */
	for (checksum = 0, ptr = (uint32_t *)meta,
	    i = 0; i < meta->config_size; i++)
		checksum += *ptr++;
	if (checksum != 0) {
		G_RAID_DEBUG(1, "NVIDIA checksum check failed on %s", pp->name);
		free(meta, M_MD_NVIDIA);
		return (NULL);
	}

	/* Check volume state. */
	if (meta->state != NVIDIA_S_IDLE && meta->state != NVIDIA_S_INIT &&
	    meta->state != NVIDIA_S_REBUILD && meta->state != NVIDIA_S_SYNC) {
		G_RAID_DEBUG(1, "NVIDIA unknown state on %s (0x%02x)",
		    pp->name, meta->state);
		free(meta, M_MD_NVIDIA);
		return (NULL);
	}

	/* Check raid type. */
	if (meta->type != NVIDIA_T_RAID0 && meta->type != NVIDIA_T_RAID1 &&
	    meta->type != NVIDIA_T_RAID3 && meta->type != NVIDIA_T_RAID5 &&
	    meta->type != NVIDIA_T_RAID5_SYM &&
	    meta->type != NVIDIA_T_RAID01 && meta->type != NVIDIA_T_CONCAT) {
		G_RAID_DEBUG(1, "NVIDIA unknown RAID level on %s (0x%02x)",
		    pp->name, meta->type);
		free(meta, M_MD_NVIDIA);
		return (NULL);
	}

	return (meta);
}