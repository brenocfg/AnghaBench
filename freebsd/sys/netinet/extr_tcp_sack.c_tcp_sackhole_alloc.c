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
typedef  void* tcp_seq ;
struct tcpcb {scalar_t__ snd_numholes; } ;
struct sackhole {void* rxmit; void* end; void* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_sack_hole_zone ; 
 scalar_t__ V_tcp_sack_globalholes ; 
 scalar_t__ V_tcp_sack_globalmaxholes ; 
 scalar_t__ V_tcp_sack_maxholes ; 
 int /*<<< orphan*/  atomic_add_int (scalar_t__*,int) ; 
 int /*<<< orphan*/  tcps_sack_sboverflow ; 
 scalar_t__ uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sackhole *
tcp_sackhole_alloc(struct tcpcb *tp, tcp_seq start, tcp_seq end)
{
	struct sackhole *hole;

	if (tp->snd_numholes >= V_tcp_sack_maxholes ||
	    V_tcp_sack_globalholes >= V_tcp_sack_globalmaxholes) {
		TCPSTAT_INC(tcps_sack_sboverflow);
		return NULL;
	}

	hole = (struct sackhole *)uma_zalloc(V_sack_hole_zone, M_NOWAIT);
	if (hole == NULL)
		return NULL;

	hole->start = start;
	hole->end = end;
	hole->rxmit = start;

	tp->snd_numholes++;
	atomic_add_int(&V_tcp_sack_globalholes, 1);

	return hole;
}