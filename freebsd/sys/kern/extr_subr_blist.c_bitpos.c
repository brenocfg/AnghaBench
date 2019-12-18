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
typedef  int /*<<< orphan*/  u_daddr_t ;
typedef  int /*<<< orphan*/  mask ;

/* Variables and functions */
 int /*<<< orphan*/  ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffsll (int /*<<< orphan*/ ) ; 
 int generic_bitpos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bitpos(u_daddr_t mask)
{

	switch (sizeof(mask)) {
#ifdef HAVE_INLINE_FFSLL
	case sizeof(long long):
		return (ffsll(mask) - 1);
#endif
#ifdef HAVE_INLINE_FFS
	case sizeof(int):
		return (ffs(mask) - 1);
#endif
	default:
		return (generic_bitpos(mask));
	}
}