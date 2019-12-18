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
union __fpscr {TYPE_1__ __bits; int /*<<< orphan*/  __d; } ;

/* Variables and functions */
 int _ROUND_MASK ; 
 int /*<<< orphan*/  __mffs (int /*<<< orphan*/ *) ; 

inline int
fegetround(void)
{
	union __fpscr __r;

	__mffs(&__r.__d);
	return (__r.__bits.__reg & _ROUND_MASK);
}