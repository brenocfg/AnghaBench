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
typedef  TYPE_1__* wi_t ;
struct wi_struct {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  private_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wi_private_free (int /*<<< orphan*/ ) ; 

void wi_free(wi_t self) {
  if (self) {
    wi_private_free(self->private_state);
    memset(self, 0, sizeof(struct wi_struct));
    free(self);
  }
}