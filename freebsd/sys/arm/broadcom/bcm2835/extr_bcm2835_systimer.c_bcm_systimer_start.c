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
typedef  int uint32_t ;
struct systimer {int index; int enabled; } ;
struct eventtimer {scalar_t__ et_frequency; struct systimer* et_priv; } ;
typedef  int sbintime_t ;
typedef  int /*<<< orphan*/  register_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SYSTIMER_C0 ; 
 int /*<<< orphan*/  SYSTIMER_CLO ; 
 scalar_t__ SYSTIMER_CS ; 
 int bcm_systimer_tc_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_systimer_tc_write_4 (scalar_t__,int) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_systimer_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{
	struct systimer *st = et->et_priv;
	uint32_t clo, clo1;
	uint32_t count;
	register_t s;

	if (first != 0) {

		count = ((uint32_t)et->et_frequency * first) >> 32;

		s = intr_disable();
		clo = bcm_systimer_tc_read_4(SYSTIMER_CLO);
restart:
		clo += count;
		/*
		 * Clear pending interrupts
		 */
		bcm_systimer_tc_write_4(SYSTIMER_CS, (1 << st->index));
		bcm_systimer_tc_write_4(SYSTIMER_C0 + st->index*4, clo);
		clo1 = bcm_systimer_tc_read_4(SYSTIMER_CLO);
		if ((int32_t)(clo1 - clo) >= 0) {
			count *= 2;
			clo = clo1;
			goto restart;
		}
		st->enabled = 1;
		intr_restore(s);

		return (0);
	}

	return (EINVAL);
}