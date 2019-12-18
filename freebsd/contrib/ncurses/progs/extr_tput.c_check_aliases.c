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
 int /*<<< orphan*/  PROG_INIT ; 
 int /*<<< orphan*/  PROG_RESET ; 
 void* is_init ; 
 void* is_reset ; 
 void* same_program (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_aliases(const char *name)
{
    is_init = same_program(name, PROG_INIT);
    is_reset = same_program(name, PROG_RESET);
}