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
struct rand_data {scalar_t__ old_data; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  jent_fips_enabled () ; 
 int /*<<< orphan*/  jent_gen_entropy (struct rand_data*) ; 
 int /*<<< orphan*/  jent_panic (char*) ; 

__attribute__((used)) static void jent_fips_test(struct rand_data *ec)
{
	if (!jent_fips_enabled())
		return;

	/* prime the FIPS test */
	if (!ec->old_data) {
		ec->old_data = ec->data;
		jent_gen_entropy(ec);
	}

	if (ec->data == ec->old_data)
		jent_panic("jitterentropy: Duplicate output detected\n");

	ec->old_data = ec->data;
}