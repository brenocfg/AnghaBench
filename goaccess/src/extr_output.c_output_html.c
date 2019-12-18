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
struct TYPE_2__ {scalar_t__ json_pretty_print; } ;
typedef  int /*<<< orphan*/  GLog ;
typedef  int /*<<< orphan*/  GHolder ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DATE_TIME ; 
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  generate_time () ; 
 int nlines ; 
 int /*<<< orphan*/  now_tm ; 
 int /*<<< orphan*/  print_conn_def (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_html_body (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_html_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_html_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_json_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_json_defs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_json_nlines (int) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 

void
output_html (GLog * glog, GHolder * holder, const char *filename)
{
  FILE *fp;
  char now[DATE_TIME];

  if (filename != NULL)
    fp = fopen (filename, "w");
  else
    fp = stdout;

  if (!fp)
    FATAL ("Unable to open HTML file: %s.", strerror (errno));

  /* use new lines to prettify output */
  if (conf.json_pretty_print)
    nlines = 1;
  set_json_nlines (nlines);

  generate_time ();
  strftime (now, DATE_TIME, "%Y-%m-%d %H:%M:%S %z", now_tm);

  print_html_header (fp);

  print_html_body (fp, now);
  print_json_defs (fp);
  print_json_data (fp, glog, holder);
  print_conn_def (fp);

  print_html_footer (fp);

  fclose (fp);
}