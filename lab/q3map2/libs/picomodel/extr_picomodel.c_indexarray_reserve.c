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
typedef  int /*<<< orphan*/  picoIndex_t ;
struct TYPE_3__ {int /*<<< orphan*/  last; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ IndexArray ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_calloc (size_t,int) ; 

void indexarray_reserve(IndexArray* self, size_t size) {
	self->data = self->last = _pico_calloc(size, sizeof(picoIndex_t));
}