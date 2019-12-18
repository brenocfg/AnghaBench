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
struct dbm_page {int /*<<< orphan*/ * arch; int /*<<< orphan*/ * sect; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lstcat (char*,size_t*,int /*<<< orphan*/ *,char*) ; 
 int lstlen (int /*<<< orphan*/ *,int) ; 
 char* mandoc_malloc (size_t) ; 

__attribute__((used)) static char *
buildnames(const struct dbm_page *page)
{
	char	*buf;
	size_t	 i, sz;

	sz = lstlen(page->name, 2) + 1 + lstlen(page->sect, 2) +
	    (page->arch == NULL ? 0 : 1 + lstlen(page->arch, 2)) + 2;
	buf = mandoc_malloc(sz);
	i = 0;
	lstcat(buf, &i, page->name, ", ");
	buf[i++] = '(';
	lstcat(buf, &i, page->sect, ", ");
	if (page->arch != NULL) {
		buf[i++] = '/';
		lstcat(buf, &i, page->arch, ", ");
	}
	buf[i++] = ')';
	buf[i++] = '\0';
	assert(i == sz);
	return buf;
}