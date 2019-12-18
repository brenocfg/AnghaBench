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
struct nat44_cfg_nat {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int stringnum_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
natname_cmp(const void *a, const void *b)
{
	struct nat44_cfg_nat *ia, *ib;

	ia = (struct nat44_cfg_nat *)a;
	ib = (struct nat44_cfg_nat *)b;

	return (stringnum_cmp(ia->name, ib->name));
}