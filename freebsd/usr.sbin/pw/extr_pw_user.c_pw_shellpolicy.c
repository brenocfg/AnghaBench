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
struct userconf {int /*<<< orphan*/  shell_default; int /*<<< orphan*/  shells; int /*<<< orphan*/  shelldir; } ;

/* Variables and functions */
 char* shell_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
pw_shellpolicy(struct userconf * cnf)
{

	return shell_path(cnf->shelldir, cnf->shells, cnf->shell_default);
}