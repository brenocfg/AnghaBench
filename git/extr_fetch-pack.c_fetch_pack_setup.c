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
 int /*<<< orphan*/  fetch_pack_config () ; 
 scalar_t__ fetch_unpack_limit ; 
 scalar_t__ transfer_unpack_limit ; 
 scalar_t__ unpack_limit ; 

__attribute__((used)) static void fetch_pack_setup(void)
{
	static int did_setup;
	if (did_setup)
		return;
	fetch_pack_config();
	if (0 <= transfer_unpack_limit)
		unpack_limit = transfer_unpack_limit;
	else if (0 <= fetch_unpack_limit)
		unpack_limit = fetch_unpack_limit;
	did_setup = 1;
}