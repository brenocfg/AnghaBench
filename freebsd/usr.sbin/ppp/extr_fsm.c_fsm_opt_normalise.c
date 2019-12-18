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
struct fsm_decode {scalar_t__ rejend; scalar_t__ rej; scalar_t__ nakend; scalar_t__ nak; int /*<<< orphan*/  ack; int /*<<< orphan*/  ackend; } ;

/* Variables and functions */

void
fsm_opt_normalise(struct fsm_decode *dec)
{
  if (dec->rejend != dec->rej) {
    /* rejects are preferred */
    dec->ackend = dec->ack;
    dec->nakend = dec->nak;
  } else if (dec->nakend != dec->nak)
    /* then NAKs */
    dec->ackend = dec->ack;
}