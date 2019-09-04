#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numpoints; int /*<<< orphan*/ ** p; } ;
typedef  TYPE_1__ winding_t ;
struct TYPE_5__ {TYPE_1__* winding; } ;
typedef  TYPE_2__ portal_t ;

/* Variables and functions */
 int /*<<< orphan*/  Sys_Printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PrintPortal( portal_t *p ){
	int i;
	winding_t   *w;

	w = p->winding;
	for ( i = 0 ; i < w->numpoints ; i++ )
		Sys_Printf( "(%5.0f,%5.0f,%5.0f)\n",w->p[i][0]
					, w->p[i][1], w->p[i][2] );
}