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
typedef  TYPE_1__* cb_t ;
struct TYPE_4__ {struct TYPE_4__* begin; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void cb_free(cb_t self) {
  if (self) {
    if (self->begin) {
      free(self->begin);
    }
    free(self);
  }
}