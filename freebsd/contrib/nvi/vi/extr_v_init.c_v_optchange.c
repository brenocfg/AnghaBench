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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
#define  O_MATCHCHARS 131 
#define  O_PARAGRAPHS 130 
#define  O_SECTIONS 129 
 char* O_STR (int /*<<< orphan*/ *,int const) ; 
#define  O_WINDOW 128 
 int v_buildmcs (int /*<<< orphan*/ *,char*) ; 
 int v_buildps (int /*<<< orphan*/ *,char*,char*) ; 
 int vs_crel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
v_optchange(SCR *sp, int offset, char *str, u_long *valp)
{
	switch (offset) {
	case O_MATCHCHARS:
		return (v_buildmcs(sp, str));
	case O_PARAGRAPHS:
		return (v_buildps(sp, str, O_STR(sp, O_SECTIONS)));
	case O_SECTIONS:
		return (v_buildps(sp, O_STR(sp, O_PARAGRAPHS), str));
	case O_WINDOW:
		return (vs_crel(sp, *valp));
	}
	return (0);
}