#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sack_bytes_rexmit; int sacked_bytes; } ;
struct tcpcb {int snd_max; int snd_una; TYPE_1__ sackhint; } ;

/* Variables and functions */

int
tcp_compute_pipe(struct tcpcb *tp)
{
	return (tp->snd_max - tp->snd_una +
		tp->sackhint.sack_bytes_rexmit -
		tp->sackhint.sacked_bytes);
}