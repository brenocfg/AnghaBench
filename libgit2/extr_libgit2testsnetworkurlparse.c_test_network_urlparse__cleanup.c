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
 int /*<<< orphan*/  conndata ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gitno_connection_data_free_ptrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * host ; 
 int /*<<< orphan*/ * pass ; 
 int /*<<< orphan*/ * path ; 
 int /*<<< orphan*/ * port ; 
 int /*<<< orphan*/ * user ; 

void test_network_urlparse__cleanup(void)
{
#define FREE_AND_NULL(x) if (x) { git__free(x); x = NULL; }
	FREE_AND_NULL(host);
	FREE_AND_NULL(port);
	FREE_AND_NULL(path);
	FREE_AND_NULL(user);
	FREE_AND_NULL(pass);

	gitno_connection_data_free_ptrs(&conndata);
}