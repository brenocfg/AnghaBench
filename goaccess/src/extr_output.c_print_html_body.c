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
struct TYPE_2__ {char* html_report_title; scalar_t__ no_html_last_updated; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* INFO_LAST_UPDATED ; 
 char* T_DASH ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 char* tpls ; 

__attribute__((used)) static void
print_html_body (FILE * fp, const char *now)
{
  fprintf (fp,
  "<nav class='hidden-xs hidden-sm hide'>"
  "</nav>"

  "<i class='spinner fa fa-circle-o-notch fa-spin fa-3x fa-fw'></i>"
  "<div class='container hide'>"
  "<div class='wrap-header'>"
  "<div class='row row-offcanvas row-offcanvas-right'>"
  "<div class='col-md-12'>"
  "<div class='page-header clearfix'>"
  "<div class='pull-right'>"
  "<h4>"
  "<span class='label label-info' style='display:%s'>"
  "<span class='hidden-xs'>%s: </span>"
  "<span class='last-updated'>%s</span>"
  "</span>"
  "</h4>"
  "</div>"
  "<h1>"
  "<span class='hidden-xs hidden-sm'>"
  "<i class='fa fa-tachometer'></i> %s"
  "</span>"
  "<span class='visible-xs visible-sm'>"
  "<i class='fa fa-bars nav-minibars'></i>"
  "<i class='fa fa-circle nav-ws-status mini'></i>"
  "</span>"
  "</h1>", conf.no_html_last_updated ? "none" : "block", INFO_LAST_UPDATED, now, T_DASH);

  fprintf (fp,
  "<div class='report-title'>%s</div>"
  "</div>"
  "<div class='wrap-general'></div>"
  "</div>"
  "</div>"
  "</div>"
  "<div class='wrap-panels'></div>"
  "</div>", conf.html_report_title ? conf.html_report_title : "");

  fprintf (fp, "%s", tpls);
}