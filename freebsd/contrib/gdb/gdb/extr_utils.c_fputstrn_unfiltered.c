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
struct ui_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered ; 
 int /*<<< orphan*/  fputs_unfiltered ; 
 int /*<<< orphan*/  printchar (char const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ui_file*,int) ; 

void
fputstrn_unfiltered (const char *str, int n, int quoter,
		     struct ui_file *stream)
{
  int i;
  for (i = 0; i < n; i++)
    printchar (str[i], fputs_unfiltered, fprintf_unfiltered, stream, quoter);
}