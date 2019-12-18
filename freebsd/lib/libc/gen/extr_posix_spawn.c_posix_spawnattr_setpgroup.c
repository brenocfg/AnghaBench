#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* posix_spawnattr_t ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_3__ {int /*<<< orphan*/  sa_pgroup; } ;

/* Variables and functions */

int
posix_spawnattr_setpgroup(posix_spawnattr_t *sa, pid_t pgroup)
{
	(*sa)->sa_pgroup = pgroup;
	return (0);
}