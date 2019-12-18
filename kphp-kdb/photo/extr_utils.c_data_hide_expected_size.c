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
struct TYPE_5__ {int real_n; } ;
struct TYPE_4__ {TYPE_2__ hidden_state; } ;
typedef  TYPE_1__ data ;

/* Variables and functions */
 int lookup_save_expected_len (TYPE_2__*) ; 

int data_hide_expected_size (data *d) {
#ifdef LOOKUP_CNT
  return d->hidden_state.real_n;
#else
  return lookup_save_expected_len (&d->hidden_state);
#endif
}