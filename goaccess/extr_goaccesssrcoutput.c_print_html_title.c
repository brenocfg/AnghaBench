#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* html_report_title; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* HTML_REPORT_TITLE ; 
 int /*<<< orphan*/  clean_output (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
print_html_title (FILE * fp)
{
  const char *title =
    conf.html_report_title ? conf.html_report_title : HTML_REPORT_TITLE;

  fprintf (fp, "<title>");
  clean_output (fp, (char *) title);
  fprintf (fp, "</title>");
}