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
 int PROCESS_DIRS ; 
 int PROCESS_FILES ; 
 int RECURSIVE ; 
 int /*<<< orphan*/  process_ls_ref ; 
 int /*<<< orphan*/  remote_ls (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_dav_remote_heads(void)
{
	remote_ls("refs/", (PROCESS_FILES | PROCESS_DIRS | RECURSIVE), process_ls_ref, NULL);
}