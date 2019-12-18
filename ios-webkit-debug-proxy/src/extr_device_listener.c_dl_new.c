#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dl_struct {int dummy; } ;
struct dl_private {int dummy; } ;
typedef  scalar_t__ ht_t ;
typedef  TYPE_1__* dl_t ;
typedef  TYPE_1__* dl_private_t ;
typedef  TYPE_1__* cb_t ;
struct TYPE_8__ {scalar_t__ device_num_to_device_id; struct TYPE_8__* in; struct TYPE_8__* private_state; int /*<<< orphan*/  on_recv; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_INT_KEYS ; 
 TYPE_1__* cb_new () ; 
 int /*<<< orphan*/  dl_on_recv ; 
 int /*<<< orphan*/  dl_start ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ ht_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

dl_t dl_new() {
  dl_t self = (dl_t)malloc(sizeof(struct dl_struct));
  dl_private_t my = (dl_private_t)malloc(sizeof(struct dl_private));
  cb_t in = cb_new();
  ht_t d_ht = ht_new(HT_INT_KEYS);
  if (!self || !my || !in || !d_ht) {
    free(self);
    free(my);
    free(in);
    return NULL;
  }
  memset(self, 0, sizeof(struct dl_struct));
  memset(my, 0, sizeof(struct dl_private));
  self->start = dl_start;
  self->on_recv = dl_on_recv;
  self->private_state = my;
  my->in = in;
  my->device_num_to_device_id = d_ht;
  return self;
}