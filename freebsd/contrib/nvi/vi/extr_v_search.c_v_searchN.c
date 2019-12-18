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
typedef  int dir_t ;
typedef  int /*<<< orphan*/  VICMD ;
struct TYPE_4__ {int searchdir; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
#define  BACKWARD 129 
#define  FORWARD 128 
 int /*<<< orphan*/  SEARCH_PARSE ; 
 int v_search (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
v_searchN(SCR *sp, VICMD *vp)
{
	dir_t dir;

	switch (sp->searchdir) {
	case BACKWARD:
		dir = FORWARD;
		break;
	case FORWARD:
		dir = BACKWARD;
		break;
	default:
		dir = sp->searchdir;
		break;
	}
	return (v_search(sp, vp, NULL, 0, SEARCH_PARSE, dir));
}