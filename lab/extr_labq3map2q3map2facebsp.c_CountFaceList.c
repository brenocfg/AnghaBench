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
typedef  TYPE_1__ face_t ;

/* Variables and functions */

int CountFaceList( face_t *list ){
	int c;


	c = 0;
	for ( ; list != NULL; list = list->next )
		c++;
	return c;
}