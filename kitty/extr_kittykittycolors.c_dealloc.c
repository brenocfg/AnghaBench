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
struct TYPE_2__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  ColorProfile ;

/* Variables and functions */
 TYPE_1__* Py_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dealloc(ColorProfile* self) {
    Py_TYPE(self)->tp_free((PyObject*)self);
}