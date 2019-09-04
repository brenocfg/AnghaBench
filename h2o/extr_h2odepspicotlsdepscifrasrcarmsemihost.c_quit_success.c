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
 int /*<<< orphan*/  OP_EXIT ; 
 scalar_t__ OP_EXIT_ARG_SUCCESS ; 
 int /*<<< orphan*/  semihost (int /*<<< orphan*/ ,void*) ; 

__attribute__((noreturn))
void quit_success(void)
{
  semihost(OP_EXIT, (void *) OP_EXIT_ARG_SUCCESS);
  while (1)
    ;
}