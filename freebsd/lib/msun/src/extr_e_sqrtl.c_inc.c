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
struct TYPE_2__ {scalar_t__ manl; scalar_t__ manh; int /*<<< orphan*/  exp; } ;
union IEEEl2bits {long double e; TYPE_1__ bits; } ;

/* Variables and functions */
 scalar_t__ LDBL_NBIT ; 

__attribute__((used)) static inline long double
inc(long double x)
{
	union IEEEl2bits u;

	u.e = x;
	if (++u.bits.manl == 0) {
		if (++u.bits.manh == 0) {
			u.bits.exp++;
			u.bits.manh |= LDBL_NBIT;
		}
	}
	return (u.e);
}