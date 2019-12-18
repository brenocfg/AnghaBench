#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct freebsd11_stat {int dummy; } ;
struct TYPE_3__ {int gl_flags; int (* gl_lstat ) (char*,struct freebsd11_stat*) ;} ;
typedef  TYPE_1__ glob11_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int GLOB_ALTDIRFUNC ; 
 scalar_t__ MAXPATHLEN ; 
 scalar_t__ MB_LEN_MAX ; 
 int /*<<< orphan*/  errno ; 
 int freebsd11_lstat (char*,struct freebsd11_stat*) ; 
 scalar_t__ g_Ctoc (int /*<<< orphan*/ *,char*,int) ; 
 int stub1 (char*,struct freebsd11_stat*) ; 

__attribute__((used)) static int
g_lstat(Char *fn, struct freebsd11_stat *sb, glob11_t *pglob)
{
	char buf[MAXPATHLEN + MB_LEN_MAX - 1];

	if (g_Ctoc(fn, buf, sizeof(buf))) {
		errno = ENAMETOOLONG;
		return (-1);
	}
	if (pglob->gl_flags & GLOB_ALTDIRFUNC)
		return((*pglob->gl_lstat)(buf, sb));
	return (freebsd11_lstat(buf, sb));
}