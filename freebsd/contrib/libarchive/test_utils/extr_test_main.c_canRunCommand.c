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
 int /*<<< orphan*/  redirectArgs ; 
 scalar_t__ systemf (char*,char const*,int /*<<< orphan*/ ) ; 

int
canRunCommand(const char *cmd)
{
  static int tested = 0, value = 0;
  if (!tested) {
    tested = 1;
    if (systemf("%s %s", cmd, redirectArgs) == 0)
      value = 1;
  }
  return (value);
}