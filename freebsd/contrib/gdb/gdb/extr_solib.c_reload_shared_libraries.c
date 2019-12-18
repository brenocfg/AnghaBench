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
 int /*<<< orphan*/  auto_solib_add ; 
 int /*<<< orphan*/  no_shared_libraries (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  solib_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
reload_shared_libraries (char *ignored, int from_tty)
{
  no_shared_libraries (NULL, from_tty);
  solib_add (NULL, from_tty, NULL, auto_solib_add);
}