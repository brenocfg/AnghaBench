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
 int /*<<< orphan*/  EOL ; 
 char** USAGE_MINI ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void usage_mini_print (const char *progname)
{
  for (int i = 0; USAGE_MINI[i] != NULL; i++)
  {
    printf (USAGE_MINI[i], progname);

    fwrite (EOL, strlen (EOL), 1, stdout);
  }
}