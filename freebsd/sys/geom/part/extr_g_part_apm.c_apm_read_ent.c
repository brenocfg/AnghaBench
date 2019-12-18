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
typedef  int uint32_t ;
struct g_provider {int sectorsize; } ;
struct g_consumer {struct g_provider* provider; } ;
struct apm_ent {int /*<<< orphan*/  ent_type; int /*<<< orphan*/  ent_name; void* ent_size; void* ent_start; void* ent_pmblkcnt; int /*<<< orphan*/  ent_sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be16dec (char*) ; 
 void* be32dec (char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_read_data (struct g_consumer*,int,int,int*) ; 
 int /*<<< orphan*/  swab (char*,int) ; 

__attribute__((used)) static int
apm_read_ent(struct g_consumer *cp, uint32_t blk, struct apm_ent *ent,
    int tivo_series1)
{
	struct g_provider *pp;
	char *buf;
	int error;

	pp = cp->provider;
	buf = g_read_data(cp, pp->sectorsize * blk, pp->sectorsize, &error);
	if (buf == NULL)
		return (error);
	if (tivo_series1)
		swab(buf, pp->sectorsize);
	ent->ent_sig = be16dec(buf);
	ent->ent_pmblkcnt = be32dec(buf + 4);
	ent->ent_start = be32dec(buf + 8);
	ent->ent_size = be32dec(buf + 12);
	bcopy(buf + 16, ent->ent_name, sizeof(ent->ent_name));
	bcopy(buf + 48, ent->ent_type, sizeof(ent->ent_type));
	g_free(buf);
	return (0);
}