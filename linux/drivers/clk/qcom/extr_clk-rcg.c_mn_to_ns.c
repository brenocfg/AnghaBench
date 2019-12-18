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
typedef  int u32 ;
struct mn {int n_val_shift; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mn_to_ns(struct mn *mn, u32 m, u32 n, u32 ns)
{
	u32 mask;

	mask = BIT(mn->width) - 1;
	mask <<= mn->n_val_shift;
	ns &= ~mask;

	if (n) {
		n = n - m;
		n = ~n;
		n &= BIT(mn->width) - 1;
		n <<= mn->n_val_shift;
		ns |= n;
	}

	return ns;
}