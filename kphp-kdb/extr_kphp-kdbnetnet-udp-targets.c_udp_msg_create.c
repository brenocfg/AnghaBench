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
struct udp_target {int dummy; } ;
struct raw_message {int dummy; } ;
struct udp_msg {int msg_num; struct raw_message raw; struct udp_target* S; } ;

/* Variables and functions */
 struct udp_msg* zmalloc (int) ; 

struct udp_msg *udp_msg_create (struct raw_message *raw, int packet_id, struct udp_target *S) {
  struct udp_msg *msg = zmalloc (sizeof (*msg));
  msg->msg_num = packet_id;
  msg->S = S;
  msg->raw = *raw;
  return msg;
}