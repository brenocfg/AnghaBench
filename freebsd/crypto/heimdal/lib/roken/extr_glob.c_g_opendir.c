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
struct TYPE_3__ {int gl_flags; int /*<<< orphan*/ * (* gl_opendir ) (char*) ;} ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  DIR ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int GLOB_ALTDIRFUNC ; 
 int MaxPathLen ; 
 int /*<<< orphan*/  g_Ctoc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/ * stub1 (char*) ; 

__attribute__((used)) static DIR *
g_opendir(Char *str, glob_t *pglob)
{
	char buf[MaxPathLen];

	if (!*str)
		strlcpy(buf, ".", sizeof(buf));
	else
		g_Ctoc(str, buf);

	if (pglob->gl_flags & GLOB_ALTDIRFUNC)
		return((*pglob->gl_opendir)(buf));

	return(opendir(buf));
}