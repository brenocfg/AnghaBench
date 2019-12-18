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
 int /*<<< orphan*/  MM_NOKEY ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hostbased_chost ; 
 int /*<<< orphan*/ * hostbased_cuser ; 
 int /*<<< orphan*/ * key_blob ; 
 scalar_t__ key_bloblen ; 
 int /*<<< orphan*/  key_blobtype ; 
 int /*<<< orphan*/ * key_opts ; 
 int /*<<< orphan*/  sshauthopt_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
monitor_reset_key_state(void)
{
	/* reset state */
	free(key_blob);
	free(hostbased_cuser);
	free(hostbased_chost);
	sshauthopt_free(key_opts);
	key_blob = NULL;
	key_bloblen = 0;
	key_blobtype = MM_NOKEY;
	key_opts = NULL;
	hostbased_cuser = NULL;
	hostbased_chost = NULL;
}