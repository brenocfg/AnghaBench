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
typedef  int /*<<< orphan*/  quicly_sender_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_SENDER_STATE_ACKED ; 
 int /*<<< orphan*/  QUICLY_SENDER_STATE_SEND ; 

__attribute__((used)) static void on_ack_stream_state_sender(quicly_sender_state_t *sender_state, int acked)
{
    *sender_state = acked ? QUICLY_SENDER_STATE_ACKED : QUICLY_SENDER_STATE_SEND;
}