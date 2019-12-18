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
typedef  scalar_t__ uint32_t ;
struct tcpcb {scalar_t__ snd_una; scalar_t__ snd_max; } ;

/* Variables and functions */

uint32_t
ctf_outstanding(struct tcpcb *tp)
{
	return(tp->snd_max - tp->snd_una);
}