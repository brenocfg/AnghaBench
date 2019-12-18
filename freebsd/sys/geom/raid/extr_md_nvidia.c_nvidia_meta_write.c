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
struct nvidia_raid_conf {int config_size; scalar_t__ checksum; } ;
struct g_provider {int sectorsize; int /*<<< orphan*/  name; scalar_t__ mediasize; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_MD_NVIDIA ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int g_write_data (struct g_consumer*,scalar_t__,char*,int) ; 
 char* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,struct nvidia_raid_conf*,int) ; 

__attribute__((used)) static int
nvidia_meta_write(struct g_consumer *cp, struct nvidia_raid_conf *meta)
{
	struct g_provider *pp;
	char *buf;
	int error, i;
	uint32_t checksum, *ptr;

	pp = cp->provider;

	/* Recalculate checksum for case if metadata were changed. */
	meta->checksum = 0;
	for (checksum = 0, ptr = (uint32_t *)meta,
	    i = 0; i < meta->config_size; i++)
		checksum += *ptr++;
	meta->checksum -= checksum;

	/* Create and fill buffer. */
	buf = malloc(pp->sectorsize, M_MD_NVIDIA, M_WAITOK | M_ZERO);
	memcpy(buf, meta, sizeof(*meta));

	/* Write metadata. */
	error = g_write_data(cp,
	    pp->mediasize - 2 * pp->sectorsize, buf, pp->sectorsize);
	if (error != 0) {
		G_RAID_DEBUG(1, "Cannot write metadata to %s (error=%d).",
		    pp->name, error);
	}

	free(buf, M_MD_NVIDIA);
	return (error);
}