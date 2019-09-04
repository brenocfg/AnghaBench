#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_timer_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  udp_handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  udp_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_cb ; 
 int exiting ; 
 int n_receivers_ ; 
 int n_senders_ ; 
 TYPE_2__* receivers ; 
 TYPE_1__* senders ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timeout_cb(uv_timer_t* timer) {
  int i;

  exiting = 1;

  for (i = 0; i < n_senders_; i++)
    uv_close((uv_handle_t*)&senders[i].udp_handle, close_cb);

  for (i = 0; i < n_receivers_; i++)
    uv_close((uv_handle_t*)&receivers[i].udp_handle, close_cb);
}