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
struct TYPE_3__ {float distance; int /*<<< orphan*/  hit; int /*<<< orphan*/  origin; int /*<<< orphan*/  direction; int /*<<< orphan*/  displacement; int /*<<< orphan*/  end; } ;
typedef  TYPE_1__ trace_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

float SetupTrace( trace_t *trace ){
	VectorSubtract( trace->end, trace->origin, trace->displacement );
	trace->distance = VectorNormalize( trace->displacement, trace->direction );
	VectorCopy( trace->origin, trace->hit );
	return trace->distance;
}