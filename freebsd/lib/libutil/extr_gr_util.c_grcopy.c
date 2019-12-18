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
struct group {char** gr_mem; char* gr_name; char* gr_passwd; int /*<<< orphan*/  gr_gid; } ;

/* Variables and functions */
 char* stpcpy (char*,char const*) ; 

__attribute__((used)) static struct group *
grcopy(const struct group *gr, char *dst, const char *name, int ndx)
{
	int i;
	struct group *newgr;

	newgr = (struct group *)(void *)dst;	/* avoid alignment warning */
	dst += sizeof(*newgr);
	if (ndx != 0) {
		newgr->gr_mem = (char **)(void *)(dst);	/* avoid alignment warning */
		dst += (ndx + 1) * sizeof(*newgr->gr_mem);
	} else
		newgr->gr_mem = NULL;
	if (gr->gr_name != NULL) {
		newgr->gr_name = dst;
		dst = stpcpy(dst, gr->gr_name) + 1;
	} else
		newgr->gr_name = NULL;
	if (gr->gr_passwd != NULL) {
		newgr->gr_passwd = dst;
		dst = stpcpy(dst, gr->gr_passwd) + 1;
	} else
		newgr->gr_passwd = NULL;
	newgr->gr_gid = gr->gr_gid;
	i = 0;
	/* Original group struct might have a NULL gr_mem */
	if (gr->gr_mem != NULL) {
		for (; gr->gr_mem[i] != NULL; i++) {
			newgr->gr_mem[i] = dst;
			dst = stpcpy(dst, gr->gr_mem[i]) + 1;
		}
	}
	/* If name is not NULL, newgr->gr_mem is known to be not NULL */
	if (name != NULL) {
		newgr->gr_mem[i++] = dst;
		dst = stpcpy(dst, name) + 1;
	}
	/* if newgr->gr_mem is not NULL add NULL marker */
	if (newgr->gr_mem != NULL)
		newgr->gr_mem[i] = NULL;

	return (newgr);
}