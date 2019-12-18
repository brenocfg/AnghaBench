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
struct tcpcb {int dummy; } ;
struct tcp_bbr {int dummy; } ;
struct bbr_sendmap {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  TCPSTAT_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcps_sndbyte_error ; 
 int /*<<< orphan*/  tcps_sndpack_error ; 

__attribute__((used)) static inline void
bbr_do_error_accounting(struct tcpcb *tp, struct tcp_bbr *bbr, struct bbr_sendmap *rsm, int32_t len, int32_t error)
{
#ifdef NETFLIX_STATS
	TCPSTAT_INC(tcps_sndpack_error);
	TCPSTAT_ADD(tcps_sndbyte_error, len);
#endif
}