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
typedef  scalar_t__ uint16_t ;
struct jmicron_raid_conf {int /*<<< orphan*/  signature; } ;
struct g_provider {int /*<<< orphan*/  name; scalar_t__ sectorsize; scalar_t__ mediasize; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  JMICRON_MAGIC ; 
 int /*<<< orphan*/  M_MD_JMICRON ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  free (struct jmicron_raid_conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_read_data (struct g_consumer*,scalar_t__,scalar_t__,int*) ; 
 struct jmicron_raid_conf* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct jmicron_raid_conf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,scalar_t__) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct jmicron_raid_conf *
jmicron_meta_read(struct g_consumer *cp)
{
	struct g_provider *pp;
	struct jmicron_raid_conf *meta;
	char *buf;
	int error, i;
	uint16_t checksum, *ptr;

	pp = cp->provider;

	/* Read the anchor sector. */
	buf = g_read_data(cp,
	    pp->mediasize - pp->sectorsize, pp->sectorsize, &error);
	if (buf == NULL) {
		G_RAID_DEBUG(1, "Cannot read metadata from %s (error=%d).",
		    pp->name, error);
		return (NULL);
	}
	meta = (struct jmicron_raid_conf *)buf;

	/* Check if this is an JMicron RAID struct */
	if (strncmp(meta->signature, JMICRON_MAGIC, strlen(JMICRON_MAGIC))) {
		G_RAID_DEBUG(1, "JMicron signature check failed on %s", pp->name);
		g_free(buf);
		return (NULL);
	}
	meta = malloc(sizeof(*meta), M_MD_JMICRON, M_WAITOK);
	memcpy(meta, buf, min(sizeof(*meta), pp->sectorsize));
	g_free(buf);

	/* Check metadata checksum. */
	for (checksum = 0, ptr = (uint16_t *)meta, i = 0; i < 64; i++)
		checksum += *ptr++;
	if (checksum != 0) {
		G_RAID_DEBUG(1, "JMicron checksum check failed on %s", pp->name);
		free(meta, M_MD_JMICRON);
		return (NULL);
	}

	return (meta);
}