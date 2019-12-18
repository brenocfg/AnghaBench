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
typedef  int /*<<< orphan*/  uint16_t ;
struct sfxge_rxq {int dummy; } ;
typedef  enum sfxge_sw_ev { ____Placeholder_sfxge_sw_ev } sfxge_sw_ev ;

/* Variables and functions */
 int /*<<< orphan*/  sfxge_sw_ev_mk_magic (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint16_t
sfxge_sw_ev_rxq_magic(enum sfxge_sw_ev sw_ev, struct sfxge_rxq *rxq)
{
	return sfxge_sw_ev_mk_magic(sw_ev, 0);
}