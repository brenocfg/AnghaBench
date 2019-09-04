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
 int /*<<< orphan*/  MDFile (char*) ; 
 int /*<<< orphan*/  MDFilter () ; 
 int /*<<< orphan*/  MDString (char*) ; 
 int /*<<< orphan*/  MDTestSuite () ; 
 int /*<<< orphan*/  MDTimeTrial () ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char *argv[])
{
  int i;

  if (argc > 1) {
    for (i = 1; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 's')
        MDString(argv[i] + 2);
      else if (strcmp(argv[i], "-t") == 0)
        MDTimeTrial();
      else if (strcmp(argv[i], "-x") == 0)
        MDTestSuite();
      else
        MDFile(argv[i]);
    }
  } else {
    MDFilter();
  }

  return (0);
}