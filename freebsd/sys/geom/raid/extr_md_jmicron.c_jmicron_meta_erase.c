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
struct g_provider {int /*<<< orphan*/  name; scalar_t__ sectorsize; scalar_t__ mediasize; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_MD_JMICRON ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int g_write_data (struct g_consumer*,scalar_t__,char*,scalar_t__) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
jmicron_meta_erase(struct g_consumer *cp)
{
	struct g_provider *pp;
	char *buf;
	int error;

	pp = cp->provider;
	buf = malloc(pp->sectorsize, M_MD_JMICRON, M_WAITOK | M_ZERO);
	error = g_write_data(cp,
	    pp->mediasize - pp->sectorsize, buf, pp->sectorsize);
	if (error != 0) {
		G_RAID_DEBUG(1, "Cannot erase metadata on %s (error=%d).",
		    pp->name, error);
	}
	free(buf, M_MD_JMICRON);
	return (error);
}