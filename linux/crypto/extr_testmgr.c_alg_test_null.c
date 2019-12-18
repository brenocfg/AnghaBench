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
typedef  int /*<<< orphan*/  u32 ;
struct alg_test_desc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int alg_test_null(const struct alg_test_desc *desc,
			     const char *driver, u32 type, u32 mask)
{
	return 0;
}