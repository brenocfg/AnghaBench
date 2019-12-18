#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct glob_limit {int dummy; } ;
struct TYPE_4__ {size_t gl_pathc; int gl_flags; scalar_t__ gl_offs; scalar_t__ gl_pathv; } ;
typedef  TYPE_1__ glob_t ;

/* Variables and functions */
 int GLOB_NOSORT ; 
 int /*<<< orphan*/  compare ; 
 int err_nomatch (TYPE_1__*,struct glob_limit*,char const*) ; 
 int /*<<< orphan*/  qsort (scalar_t__,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
globfinal(glob_t *pglob, struct glob_limit *limit, size_t oldpathc,
    const char *origpat) {
	if (pglob->gl_pathc == oldpathc)
		return (err_nomatch(pglob, limit, origpat));

	if (!(pglob->gl_flags & GLOB_NOSORT))
		qsort(pglob->gl_pathv + pglob->gl_offs + oldpathc,
		    pglob->gl_pathc - oldpathc, sizeof(char *), compare);

	return (0);
}