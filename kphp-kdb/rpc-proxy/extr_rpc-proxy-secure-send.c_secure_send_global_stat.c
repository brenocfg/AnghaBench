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

/* Variables and functions */
 int /*<<< orphan*/  received_answer_ack_ack ; 
 int /*<<< orphan*/  resent_answer_ack ; 
 int /*<<< orphan*/  resent_queries ; 
 int /*<<< orphan*/  secure_send_s0 ; 
 int /*<<< orphan*/  secure_send_s1 ; 
 int /*<<< orphan*/  sent_answer_ack ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int secure_send_global_stat (char *buf, int len) {
  return snprintf (buf, len, 
    "resent_queries\t%lld\n"
    "resent_answer_ack\t%lld\n"
    "secure_send_state0\t%lld\n"
    "secure_send_state1\t%lld\n"
    "received_answer_ack_ack\t%lld\n"
    "sent_answer_ack\t%lld\n",
    resent_queries,
    resent_answer_ack,
    secure_send_s0,
    secure_send_s1,
    received_answer_ack_ack,
    sent_answer_ack);
}