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
struct TYPE_2__ {int /*<<< orphan*/  tablename; } ;
typedef  TYPE_1__ ipfw_xtable_info ;

/* Variables and functions */
 int stringnum_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tablename_cmp(const void *a, const void *b)
{
	ipfw_xtable_info *ia, *ib;

	ia = (ipfw_xtable_info *)a;
	ib = (ipfw_xtable_info *)b;

	return (stringnum_cmp(ia->tablename, ib->tablename));
}