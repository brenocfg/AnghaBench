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
 scalar_t__* line ; 

__attribute__((used)) static void
dont_repeat_command (char *ignored, int from_tty)
{
  *line = 0;			/* Can't call dont_repeat here because we're not
				   necessarily reading from stdin.  */
}