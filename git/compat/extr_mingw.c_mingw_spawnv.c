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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  mingw_spawnve_fd (char const*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static pid_t mingw_spawnv(const char *cmd, const char **argv, int prepend_cmd)
{
	return mingw_spawnve_fd(cmd, argv, NULL, NULL, prepend_cmd, 0, 1, 2);
}