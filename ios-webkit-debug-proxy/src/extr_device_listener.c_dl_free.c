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
struct dl_struct {int dummy; } ;
struct dl_private {int dummy; } ;
typedef  TYPE_1__* dl_t ;
typedef  TYPE_1__* dl_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  device_num_to_device_id; int /*<<< orphan*/  in; struct TYPE_6__* private_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  cb_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ht_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void dl_free(dl_t self) {
  if (self) {
    dl_private_t my = self->private_state;
    if (my) {
      cb_free(my->in);
      ht_free(my->device_num_to_device_id);
      memset(my, 0, sizeof(struct dl_private));
      free(my);
    }
    memset(self, 0, sizeof(struct dl_struct));
    free(self);
  }
}