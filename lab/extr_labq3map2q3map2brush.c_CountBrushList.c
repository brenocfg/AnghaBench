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
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ brush_t ;

/* Variables and functions */

int CountBrushList( brush_t *brushes ){
	int c = 0;


	/* count brushes */
	for ( ; brushes != NULL; brushes = brushes->next )
		c++;
	return c;
}