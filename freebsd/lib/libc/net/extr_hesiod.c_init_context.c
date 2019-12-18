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

/* Variables and functions */
 int /*<<< orphan*/  HES_ER_CONFIG ; 
 int /*<<< orphan*/  HES_ER_OK ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errval ; 
 scalar_t__ hesiod_init (int /*<<< orphan*/ *) ; 
 int inited ; 

__attribute__((used)) static int
init_context()
{
	if (!inited) {
		inited = 1;
		if (hesiod_init(&context) < 0) {
			errval = HES_ER_CONFIG;
			return -1;
		}
		errval = HES_ER_OK;
	}
	return 0;
}