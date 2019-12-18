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
struct TYPE_4__ {int /*<<< orphan*/ * w; struct TYPE_4__* next; } ;
typedef  TYPE_1__ light_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* lights ; 
 scalar_t__ numLights ; 

void RadFreeLights( void ){
	light_t     *light, *next;


	/* delete lights */
	for ( light = lights; light; light = next )
	{
		next = light->next;
		if ( light->w != NULL ) {
			FreeWinding( light->w );
		}
		free( light );
	}
	numLights = 0;
	lights = NULL;
}