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
typedef  int /*<<< orphan*/  GS ;

/* Variables and functions */
 int /*<<< orphan*/  GO_TERM ; 
 char* OG_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* XTERM_RENAME ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

void
cl_setname(GS *gp, char *name)
{
/* X11 xterm escape sequence to rename the icon/window. */
#define	XTERM_RENAME	"\033]0;%s\007"

	(void)printf(XTERM_RENAME, name == NULL ? OG_STR(gp, GO_TERM) : name);
	(void)fflush(stdout);
#undef XTERM_RENAME
}