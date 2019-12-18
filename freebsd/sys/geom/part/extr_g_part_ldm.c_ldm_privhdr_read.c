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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
struct g_provider {int /*<<< orphan*/  name; int /*<<< orphan*/  sectorsize; } ;
struct g_consumer {struct g_provider* provider; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LDM_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDM_PH_SIGN ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_read_data (struct g_consumer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_char*
ldm_privhdr_read(struct g_consumer *cp, uint64_t off, int *error)
{
	struct g_provider *pp;
	u_char *buf;

	pp = cp->provider;
	buf = g_read_data(cp, off, pp->sectorsize, error);
	if (buf == NULL)
		return (NULL);

	if (memcmp(buf, LDM_PH_SIGN, strlen(LDM_PH_SIGN)) != 0) {
		LDM_DEBUG(1, "%s: invalid LDM private header signature",
		    pp->name);
		g_free(buf);
		buf = NULL;
		*error = EINVAL;
	}
	return (buf);
}