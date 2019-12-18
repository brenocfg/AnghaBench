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
struct fsm_opt {int dummy; } ;
struct fsm_decode {scalar_t__ ack; scalar_t__ ackend; } ;

/* Variables and functions */
 scalar_t__ FSM_OPTLEN ; 
 scalar_t__ fsm_opt (scalar_t__,scalar_t__,struct fsm_opt const*) ; 

void
fsm_ack(struct fsm_decode *dec, const struct fsm_opt *o)
{
  if (!dec)
    return;
  dec->ackend += fsm_opt(dec->ackend, FSM_OPTLEN - (dec->ackend - dec->ack), o);
}