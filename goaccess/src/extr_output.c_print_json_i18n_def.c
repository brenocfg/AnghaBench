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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const***) ; 
#define  GO_VERSION 157 
#define  HTML_REPORT_NAV_AH_SMALL 156 
#define  HTML_REPORT_NAV_AH_SMALL_TITLE 155 
#define  HTML_REPORT_NAV_BRIGHT 154 
#define  HTML_REPORT_NAV_DARK_BLUE 153 
#define  HTML_REPORT_NAV_DARK_GRAY 152 
#define  HTML_REPORT_NAV_DARK_PURPLE 151 
#define  HTML_REPORT_NAV_DISPLAY_TABLES 150 
#define  HTML_REPORT_NAV_EXPORT_JSON 149 
#define  HTML_REPORT_NAV_FILE_OPTS 148 
#define  HTML_REPORT_NAV_HOR 147 
#define  HTML_REPORT_NAV_ITEMS_PER_PAGE 146 
#define  HTML_REPORT_NAV_LAYOUT 145 
#define  HTML_REPORT_NAV_PANELS 144 
#define  HTML_REPORT_NAV_TABLES 143 
#define  HTML_REPORT_NAV_THEME 142 
#define  HTML_REPORT_NAV_VER 141 
#define  HTML_REPORT_PANEL_AREA_SPLINE 140 
#define  HTML_REPORT_PANEL_BAR 139 
#define  HTML_REPORT_PANEL_CHART 138 
#define  HTML_REPORT_PANEL_CHART_OPTS 137 
#define  HTML_REPORT_PANEL_FIRST 136 
#define  HTML_REPORT_PANEL_LAST 135 
#define  HTML_REPORT_PANEL_NEXT 134 
#define  HTML_REPORT_PANEL_PANEL_OPTS 133 
#define  HTML_REPORT_PANEL_PLOT_METRIC 132 
#define  HTML_REPORT_PANEL_PREVIOUS 131 
#define  HTML_REPORT_PANEL_TABLE_COLS 130 
#define  HTML_REPORT_PANEL_TYPE 129 
#define  T_HEAD 128 
 int /*<<< orphan*/  _ (char const*) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  fpclose_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fpopen_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpskeysval (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_json_i18n_def (FILE * fp)
{
  int sp = 0;
  size_t i = 0;

  /* *INDENT-OFF* */
  static const char *json_i18n[][2] = {
    {"theme"          , HTML_REPORT_NAV_THEME}          ,
    {"dark_gray"      , HTML_REPORT_NAV_DARK_GRAY}      ,
    {"bright"         , HTML_REPORT_NAV_BRIGHT}         ,
    {"dark_blue"      , HTML_REPORT_NAV_DARK_BLUE}      ,
    {"dark_purple"    , HTML_REPORT_NAV_DARK_PURPLE}    ,
    {"panels"         , HTML_REPORT_NAV_PANELS}         ,
    {"items_per_page" , HTML_REPORT_NAV_ITEMS_PER_PAGE} ,
    {"tables"         , HTML_REPORT_NAV_TABLES}         ,
    {"display_tables" , HTML_REPORT_NAV_DISPLAY_TABLES} ,
    {"ah_small"       , HTML_REPORT_NAV_AH_SMALL}       ,
    {"ah_small_title" , HTML_REPORT_NAV_AH_SMALL_TITLE} ,
    {"layout"         , HTML_REPORT_NAV_LAYOUT}         ,
    {"horizontal"     , HTML_REPORT_NAV_HOR}            ,
    {"vertical"       , HTML_REPORT_NAV_VER}            ,
    {"file_opts"      , HTML_REPORT_NAV_FILE_OPTS}      ,
    {"export_json"    , HTML_REPORT_NAV_EXPORT_JSON}    ,
    {"panel_opts"     , HTML_REPORT_PANEL_PANEL_OPTS}   ,
    {"previous"       , HTML_REPORT_PANEL_PREVIOUS}     ,
    {"next"           , HTML_REPORT_PANEL_NEXT}         ,
    {"first"          , HTML_REPORT_PANEL_FIRST}        ,
    {"last"           , HTML_REPORT_PANEL_LAST}         ,
    {"chart_opts"     , HTML_REPORT_PANEL_CHART_OPTS}   ,
    {"chart"          , HTML_REPORT_PANEL_CHART}        ,
    {"type"           , HTML_REPORT_PANEL_TYPE}         ,
    {"area_spline"    , HTML_REPORT_PANEL_AREA_SPLINE}  ,
    {"bar"            , HTML_REPORT_PANEL_BAR}          ,
    {"plot_metric"    , HTML_REPORT_PANEL_PLOT_METRIC}  ,
    {"table_columns"  , HTML_REPORT_PANEL_TABLE_COLS}   ,
    {"thead"          , T_HEAD}                         ,
    {"version"        , GO_VERSION}                     ,
  };
  /* *INDENT-ON* */

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    sp = 1;

  fpopen_obj (fp, 0);
  for (i = 0; i < ARRAY_SIZE (json_i18n); ++i) {
    fpskeysval (fp, json_i18n[i][0], _(json_i18n[i][1]), sp, 0);
  }
  fpclose_obj (fp, 0, 1);
}