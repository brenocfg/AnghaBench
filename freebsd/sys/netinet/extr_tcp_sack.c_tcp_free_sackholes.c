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
struct TYPE_2__ {int /*<<< orphan*/ * nexthole; scalar_t__ sack_bytes_rexmit; } ;
struct tcpcb {scalar_t__ snd_numholes; TYPE_1__ sackhint; int /*<<< orphan*/  snd_holes; int /*<<< orphan*/  t_inpcb; } ;
struct sackhole {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct sackhole* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_sackhole_remove (struct tcpcb*,struct sackhole*) ; 

void
tcp_free_sackholes(struct tcpcb *tp)
{
	struct sackhole *q;

	INP_WLOCK_ASSERT(tp->t_inpcb);
	while ((q = TAILQ_FIRST(&tp->snd_holes)) != NULL)
		tcp_sackhole_remove(tp, q);
	tp->sackhint.sack_bytes_rexmit = 0;

	KASSERT(tp->snd_numholes == 0, ("tp->snd_numholes == 0"));
	KASSERT(tp->sackhint.nexthole == NULL,
		("tp->sackhint.nexthole == NULL"));
}