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
struct g_provider {int sectorsize; int /*<<< orphan*/  name; scalar_t__ mediasize; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_MD_SII ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int g_write_data (struct g_consumer*,scalar_t__,char*,int) ; 
 char* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sii_meta_erase(struct g_consumer *cp)
{
	struct g_provider *pp;
	char *buf;
	int error, i;

	pp = cp->provider;
	buf = malloc(pp->sectorsize, M_MD_SII, M_WAITOK | M_ZERO);
	/* Write 4 copies of metadata. */
	for (i = 0; i < 4; i++) {
		error = g_write_data(cp,
		    pp->mediasize - (pp->sectorsize * (1 + 0x200 * i)),
		    buf, pp->sectorsize);
		if (error != 0) {
			G_RAID_DEBUG(1, "Cannot erase metadata on %s (error=%d).",
			    pp->name, error);
		}
	}
	free(buf, M_MD_SII);
	return (error);
}