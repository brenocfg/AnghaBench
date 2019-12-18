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
struct tcpcb {scalar_t__ snd_numholes; } ;
struct sackhole {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  V_sack_hole_zone ; 
 scalar_t__ V_tcp_sack_globalholes ; 
 int /*<<< orphan*/  atomic_subtract_int (scalar_t__*,int) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct sackhole*) ; 

__attribute__((used)) static void
tcp_sackhole_free(struct tcpcb *tp, struct sackhole *hole)
{

	uma_zfree(V_sack_hole_zone, hole);

	tp->snd_numholes--;
	atomic_subtract_int(&V_tcp_sack_globalholes, 1);

	KASSERT(tp->snd_numholes >= 0, ("tp->snd_numholes >= 0"));
	KASSERT(V_tcp_sack_globalholes >= 0, ("tcp_sack_globalholes >= 0"));
}