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
struct _s_x {int /*<<< orphan*/ * s; } ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,char*,int /*<<< orphan*/ *) ; 

size_t
concat_tokens(char *buf, size_t bufsize, struct _s_x *table, char *delimiter)
{
	struct _s_x *pt;
	int l;
	size_t sz;

	for (sz = 0, pt = table ; pt->s != NULL; pt++) {
		l = snprintf(buf + sz, bufsize - sz, "%s%s",
		    (sz == 0) ? "" : delimiter, pt->s);
		sz += l;
		bufsize += l;
		if (sz > bufsize)
			return (bufsize);
	}

	return (sz);
}