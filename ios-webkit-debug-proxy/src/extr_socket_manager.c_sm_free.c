#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sm_struct {int dummy; } ;
typedef  TYPE_1__* sm_t ;
struct TYPE_5__ {int /*<<< orphan*/  private_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sm_private_free (int /*<<< orphan*/ ) ; 

void sm_free(sm_t self) {
  if (self) {
    sm_private_free(self->private_state);
    memset(self, 0, sizeof(struct sm_struct));
    free(self);
  }
}