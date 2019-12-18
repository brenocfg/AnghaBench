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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
    fprintf(stderr,
      "Usage: chat [-esSvV] [-f chat-file] [-r report-file] [-t timeout]\n"
      "            [-T phone-number] [-U phone-number2] [chat-script]\n"
      "where chat-script has the form:\n"
      "            [...[[expect[-send[-expect...]] send expect[-send[-expect]] ...]]]\n");
    exit(1);
}