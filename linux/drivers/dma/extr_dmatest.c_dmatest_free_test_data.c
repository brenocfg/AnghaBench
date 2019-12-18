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
struct dmatest_data {int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dmatest_free_test_data (struct dmatest_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmatest_free_test_data(struct dmatest_data *d)
{
	__dmatest_free_test_data(d, d->cnt);
}