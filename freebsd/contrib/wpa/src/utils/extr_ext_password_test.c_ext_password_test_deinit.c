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
struct ext_password_test_data {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct ext_password_test_data*) ; 
 int /*<<< orphan*/  str_clear_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext_password_test_deinit(void *ctx)
{
	struct ext_password_test_data *data = ctx;

	str_clear_free(data->params);
	os_free(data);
}