#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct udp_msg {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct udp_msg*) ; 
 int /*<<< orphan*/  rwm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (struct udp_msg*,int) ; 

void udp_msg_free (struct udp_msg *msg) {
  assert (msg);
  rwm_free (&msg->raw);
  zfree (msg, sizeof (*msg));
}