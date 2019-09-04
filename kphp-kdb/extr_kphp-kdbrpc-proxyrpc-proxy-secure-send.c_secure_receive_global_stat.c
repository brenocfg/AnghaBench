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
 int /*<<< orphan*/  received_answer_ack ; 
 int /*<<< orphan*/  secure_answer_allocated ; 
 int /*<<< orphan*/  sent_answer_ack_ack ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int secure_receive_global_stat (char *buf, int len) {
  return snprintf (buf, len, 
    "secure_answer_allocated\t%lld\n"
    "receive_answer_ack\t%lld\n"
    "sent_answer_ack_ack\t%lld\n"
    ,
    secure_answer_allocated,
    received_answer_ack,
    sent_answer_ack_ack
  );
}