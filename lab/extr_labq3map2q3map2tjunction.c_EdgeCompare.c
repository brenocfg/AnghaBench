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
struct TYPE_2__ {float length; } ;
typedef  TYPE_1__ originalEdge_t ;

/* Variables and functions */

int EdgeCompare( const void *elem1, const void *elem2 ) {
	float d1, d2;

	d1 = ( (originalEdge_t *)elem1 )->length;
	d2 = ( (originalEdge_t *)elem2 )->length;

	if ( d1 < d2 ) {
		return -1;
	}
	if ( d2 > d1 ) {
		return 1;
	}
	return 0;
}