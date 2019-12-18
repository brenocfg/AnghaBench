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
typedef  int fexcept_t ;

/* Variables and functions */
 int FE_ALL_EXCEPT ; 
 int FE_INVALID ; 
 int /*<<< orphan*/  __mffs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __mtfsf (int /*<<< orphan*/ ) ; 

inline int
fesetexceptflag(const fexcept_t *__flagp, int __excepts)
{
	union __fpscr __r;

	if (__excepts & FE_INVALID)
		__excepts |= FE_ALL_EXCEPT;
	__mffs(&__r.__d);
	__r.__bits.__reg &= ~__excepts;
	__r.__bits.__reg |= *__flagp & __excepts;
	__mtfsf(__r.__d);
	return (0);
}