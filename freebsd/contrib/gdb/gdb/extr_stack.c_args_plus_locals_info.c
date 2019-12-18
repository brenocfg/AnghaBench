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
 int /*<<< orphan*/  args_info (char*,int) ; 
 int /*<<< orphan*/  locals_info (char*,int) ; 

__attribute__((used)) static void
args_plus_locals_info (char *ignore, int from_tty)
{
  args_info (ignore, from_tty);
  locals_info (ignore, from_tty);
}