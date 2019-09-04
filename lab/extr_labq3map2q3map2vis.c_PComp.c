#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nummightsee; } ;
typedef  TYPE_1__ vportal_t ;

/* Variables and functions */

int PComp( const void *a, const void *b ){
	if ( ( *(vportal_t **)a )->nummightsee == ( *(vportal_t **)b )->nummightsee ) {
		return 0;
	}
	if ( ( *(vportal_t **)a )->nummightsee < ( *(vportal_t **)b )->nummightsee ) {
		return -1;
	}
	return 1;
}