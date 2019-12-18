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
struct TYPE_3__ {scalar_t__ total_bytes; } ;
struct udp_msg {TYPE_1__ raw; } ;
struct TYPE_4__ {int /*<<< orphan*/  window_size; } ;

/* Variables and functions */
 TYPE_2__* __S ; 
 int /*<<< orphan*/  udp_msg_free (struct udp_msg*) ; 

void udp_msg_confirm_free (struct udp_msg *msg) {
  __S->window_size -= msg->raw.total_bytes;
  udp_msg_free (msg);
}