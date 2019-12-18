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
struct TYPE_3__ {int /*<<< orphan*/  hidden_state; } ;
typedef  TYPE_1__ data ;

/* Variables and functions */
 int lookup_conv (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int data_get_hidden_state (data *d, int id) {
  return lookup_conv (&d->hidden_state, id, 0);
}