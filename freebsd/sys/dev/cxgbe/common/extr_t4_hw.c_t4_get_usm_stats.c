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
typedef  int u64 ;
typedef  int u32 ;
struct tp_usm_stats {int frames; int drops; int octets; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_MIB_USM_PKTS ; 
 int /*<<< orphan*/  t4_tp_mib_read (struct adapter*,int*,int,int /*<<< orphan*/ ,int) ; 

void t4_get_usm_stats(struct adapter *adap, struct tp_usm_stats *st,
		      bool sleep_ok)
{
	u32 val[4];

	t4_tp_mib_read(adap, val, 4, A_TP_MIB_USM_PKTS, sleep_ok);

	st->frames = val[0];
	st->drops = val[1];
	st->octets = ((u64)val[2] << 32) | val[3];
}