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
struct TYPE_3__ {size_t imageUsed; int* image; } ;
typedef  TYPE_1__ segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_IMAGE ; 

__attribute__((used)) static void EmitByte( segment_t *seg, int v ) {
	if ( seg->imageUsed >= MAX_IMAGE ) {
		Error( "MAX_IMAGE" );
	}
	seg->image[ seg->imageUsed ] = v;
	seg->imageUsed++;
}