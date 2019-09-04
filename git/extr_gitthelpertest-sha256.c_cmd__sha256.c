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
 int /*<<< orphan*/  GIT_HASH_SHA256 ; 
 int cmd_hash_impl (int,char const**,int /*<<< orphan*/ ) ; 

int cmd__sha256(int ac, const char **av)
{
	return cmd_hash_impl(ac, av, GIT_HASH_SHA256);
}