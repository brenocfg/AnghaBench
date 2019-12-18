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
union ring_state {scalar_t__ cidx; scalar_t__ pidx_tail; scalar_t__ pidx_head; } ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABDICATED ; 
 int /*<<< orphan*/  BUSY ; 
 int /*<<< orphan*/  IDLE ; 

__attribute__((used)) static inline uint16_t
state_to_flags(union ring_state s, int abdicate)
{

	if (s.cidx == s.pidx_tail)
		return (IDLE);
	else if (abdicate && s.pidx_tail != s.pidx_head)
		return (ABDICATED);

	return (BUSY);
}