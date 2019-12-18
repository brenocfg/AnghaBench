#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type_id; int /*<<< orphan*/  size; scalar_t__ tn; } ;
typedef  TYPE_1__ event_dump ;
struct TYPE_5__ {int /*<<< orphan*/  shifts_len; } ;

/* Variables and functions */
 TYPE_2__* types ; 

void event_dump_init (event_dump *d, int type_id) {
  d->tn = 0;
  d->type_id = type_id;
  d->size = types[type_id].shifts_len;
}