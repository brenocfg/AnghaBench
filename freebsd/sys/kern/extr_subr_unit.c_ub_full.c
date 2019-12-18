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
struct unrb {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_ffc (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static inline bool
ub_full(struct unrb *ub, int len)
{
	int first_clear;

	bit_ffc(ub->map, len, &first_clear);
	return (first_clear == -1);
}