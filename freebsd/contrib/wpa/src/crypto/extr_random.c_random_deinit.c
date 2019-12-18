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
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_close_fd () ; 
 int /*<<< orphan*/ * random_entropy_file ; 
 int /*<<< orphan*/  random_write_entropy () ; 

void random_deinit(void)
{
#ifdef __linux__
	random_close_fd();
#endif /* __linux__ */
	random_write_entropy();
	os_free(random_entropy_file);
	random_entropy_file = NULL;
}