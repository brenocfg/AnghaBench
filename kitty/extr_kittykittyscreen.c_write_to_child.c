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
struct TYPE_4__ {scalar_t__ test_child; scalar_t__ window_id; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 scalar_t__ Py_None ; 
 int /*<<< orphan*/  schedule_write_to_child (scalar_t__,int,char const*,size_t) ; 
 int /*<<< orphan*/  write_to_test_child (TYPE_1__*,char const*,size_t) ; 

__attribute__((used)) static inline void
write_to_child(Screen *self, const char *data, size_t sz) {
    if (self->window_id) schedule_write_to_child(self->window_id, 1, data, sz);
    if (self->test_child != Py_None) { write_to_test_child(self, data, sz); }
}