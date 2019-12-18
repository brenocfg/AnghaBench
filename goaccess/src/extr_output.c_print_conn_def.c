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
struct TYPE_2__ {char* ws_url; scalar_t__ port; int /*<<< orphan*/  real_time_html; scalar_t__ json_pretty_print; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int atoi (scalar_t__) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  fpclose_obj (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fpopen_obj (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fpskeyival (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  fpskeysval (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_conn_def (FILE * fp)
{
  int sp = 0;
  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    sp += 1;

  if (!conf.real_time_html)
    return;

  fprintf (fp, "<script type='text/javascript'>");
  fprintf (fp, "var connection = ");

  fpopen_obj (fp, sp);
  fpskeysval (fp, "url", (conf.ws_url ? conf.ws_url : ""), sp, 0);
  fpskeyival (fp, "port", (conf.port ? atoi (conf.port) : 7890), sp, 1);
  fpclose_obj (fp, sp, 1);

  fprintf (fp, "</script>");
}