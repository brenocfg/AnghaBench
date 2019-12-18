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
 int /*<<< orphan*/  SOLIB_ADD (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auto_solib_add ; 
 int /*<<< orphan*/  current_target ; 

__attribute__((used)) static int
load_klds_stub (void *arg)
{

	SOLIB_ADD(NULL, 1, &current_target, auto_solib_add);
	return (0);
}