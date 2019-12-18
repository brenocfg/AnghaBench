#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pc_struct {int dummy; } ;
typedef  TYPE_1__* pc_t ;
struct TYPE_6__ {scalar_t__ re; struct TYPE_6__* groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pc_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  regfree (scalar_t__) ; 

void pc_free(pc_t self) {
  if (self) {
    pc_clear(self);
    free(self->groups);
    if (self->re) {
      regfree(self->re);
    }
    memset(self, 0, sizeof(struct pc_struct));
    free(self);
  }
}