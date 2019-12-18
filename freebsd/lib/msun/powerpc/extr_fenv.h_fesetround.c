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
struct TYPE_2__ {int __reg; } ;
union __fpscr {int /*<<< orphan*/  __d; TYPE_1__ __bits; } ;

/* Variables and functions */
 int _ROUND_MASK ; 
 int /*<<< orphan*/  __mffs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __mtfsf (int /*<<< orphan*/ ) ; 

inline int
fesetround(int __round)
{
	union __fpscr __r;

	if (__round & ~_ROUND_MASK)
		return (-1);
	__mffs(&__r.__d);
	__r.__bits.__reg &= ~_ROUND_MASK;
	__r.__bits.__reg |= __round;
	__mtfsf(__r.__d);
	return (0);
}