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
 int /*<<< orphan*/  ensure_workdir_mode (char const*,int) ; 
 int /*<<< orphan*/  ensure_workdir_oid (char const*,char const*) ; 

__attribute__((used)) static void ensure_workdir(const char *path, int mode, const char *oid_str)
{
	ensure_workdir_mode(path, mode);
	ensure_workdir_oid(path, oid_str);
}