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
struct TYPE_2__ {scalar_t__ color_idx; char const* html_custom_css; char const* html_custom_js; char const* html_prefs; char const* html_report_title; int json_pretty_print; int max_items; int no_color; int no_column_names; int no_csv_summary; int no_parsing_spinner; int no_progress; int no_tab_scroll; int no_html_last_updated; char const* addr; char const* fifo_in; char const* fifo_out; int daemonize; char const* origin; char const* pidfile; char const* port; int real_time_html; char const* sslcert; char const* sslkey; char const* ws_url; char const* invalid_requests_log; scalar_t__ output_format_idx; int code444_as_404; int client_err_to_unique_count; int anonymize_ip; int store_accumulated_time; int all_static_files; int crawlers_only; int date_spec_hr; int double_decode; scalar_t__ enable_panel_idx; int hour_spec_min; int ignore_crawlers; scalar_t__ ignore_panel_idx; scalar_t__ ignore_referer_idx; int no_ip_validation; scalar_t__ hide_referer_idx; scalar_t__ ignore_status_idx; int num_tests; int process_and_exit; int real_os; scalar_t__ sort_panel_idx; scalar_t__ static_file_idx; scalar_t__ static_file_max_len; char const* geoip_database; int keep_db_files; int load_from_disk; char const* db_path; int /*<<< orphan*/  compression; void* xmmap; void* tune_lmemb; void* tune_nmemb; void* tune_bnum; void* cache_ncnum; void* cache_lcnum; int /*<<< orphan*/  static_files; int /*<<< orphan*/  sort_panels; int /*<<< orphan*/  ignore_statics; int /*<<< orphan*/  ignore_status; int /*<<< orphan*/  hide_referers; int /*<<< orphan*/  ignore_referers; int /*<<< orphan*/  ignore_panels; int /*<<< orphan*/  enable_panels; int /*<<< orphan*/  output_formats; void* color_scheme; int /*<<< orphan*/  colors; } ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  IGNORE_LEVEL_PANEL ; 
 int /*<<< orphan*/  IGNORE_LEVEL_REQ ; 
 int /*<<< orphan*/  LOG_DEBUG (char*) ; 
 scalar_t__ MAX_CUSTOM_COLORS ; 
 scalar_t__ MAX_EXTENSIONS ; 
 scalar_t__ MAX_IGNORE_REF ; 
 scalar_t__ MAX_IGNORE_STATUS ; 
 scalar_t__ MAX_OUTFORMATS ; 
 int /*<<< orphan*/  TC_BZ2 ; 
 int /*<<< orphan*/  TC_ZLIB ; 
 scalar_t__ TOTAL_MODULES ; 
 void* atoi (char const*) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  display_default_config_file () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalid_log_open (char const*) ; 
 int /*<<< orphan*/  set_array_opt (char const*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  set_date_format_str (char const*) ; 
 int /*<<< orphan*/  set_log_format_str (char const*) ; 
 int /*<<< orphan*/  set_time_format_str (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int strtol (char const*,char**,int) ; 

__attribute__((used)) static void
parse_long_opt (const char *name, const char *oarg)
{
  if (!strcmp ("no-global-config", name))
    return;

  /* LOG & DATE FORMAT OPTIONS
   * ========================= */
  /* log format */
  if (!strcmp ("log-format", name))
    set_log_format_str (oarg);

  /* time format */
  if (!strcmp ("time-format", name))
    set_time_format_str (oarg);

  /* date format */
  if (!strcmp ("date-format", name))
    set_date_format_str (oarg);

  /* USER INTERFACE OPTIONS
   * ========================= */
  /* colors */
  if (!strcmp ("color", name))
    set_array_opt (oarg, conf.colors, &conf.color_idx, MAX_CUSTOM_COLORS);

  /* color scheme */
  if (!strcmp ("color-scheme", name))
    conf.color_scheme = atoi (oarg);

  /* html custom CSS */
  if (!strcmp ("html-custom-css", name))
    conf.html_custom_css = oarg;

  /* html custom JS */
  if (!strcmp ("html-custom-js", name))
    conf.html_custom_js = oarg;

  /* html JSON object containing default preferences */
  if (!strcmp ("html-prefs", name))
    conf.html_prefs = oarg;

  /* html report title */
  if (!strcmp ("html-report-title", name))
    conf.html_report_title = oarg;

  /* json pretty print */
  if (!strcmp ("json-pretty-print", name))
    conf.json_pretty_print = 1;

  /* max items */
  if (!strcmp ("max-items", name)) {
    char *sEnd;
    int max = strtol (oarg, &sEnd, 10);
    if (oarg == sEnd || *sEnd != '\0' || errno == ERANGE)
      conf.max_items = 1;
    else
      conf.max_items = max;
  }

  /* no color */
  if (!strcmp ("no-color", name))
    conf.no_color = 1;

  /* no columns */
  if (!strcmp ("no-column-names", name))
    conf.no_column_names = 1;

  /* no csv summary */
  if (!strcmp ("no-csv-summary", name))
    conf.no_csv_summary = 1;

  /* no parsing spinner */
  if (!strcmp ("no-parsing-spinner", name))
    conf.no_parsing_spinner = 1;

  /* no progress */
  if (!strcmp ("no-progress", name))
    conf.no_progress = 1;

  /* no tab scroll */
  if (!strcmp ("no-tab-scroll", name))
    conf.no_tab_scroll = 1;

  /* no html last updated field */
  if (!strcmp ("no-html-last-updated", name))
    conf.no_html_last_updated = 1;

  /* SERVER OPTIONS
   * ========================= */
  /* address to bind to */
  if (!strcmp ("addr", name))
    conf.addr = oarg;

  /* FIFO in (read) */
  if (!strcmp ("fifo-in", name))
    conf.fifo_in = oarg;

  /* FIFO out (write) */
  if (!strcmp ("fifo-out", name))
    conf.fifo_out = oarg;

  /* run program as a Unix daemon */
  if (!strcmp ("daemonize", name))
    conf.daemonize = 1;

  /* WebSocket origin */
  if (!strcmp ("origin", name))
    conf.origin = oarg;

  /* PID file to write */
  if (!strcmp ("pid-file", name))
    conf.pidfile = oarg;

  /* port to use */
  if (!strcmp ("port", name)) {
    int port = strtol (oarg, NULL, 10);
    if (port < 0 || port > 65535)
      LOG_DEBUG (("Invalid port."));
    else
      conf.port = oarg;
  }

  /* real time HTML */
  if (!strcmp ("real-time-html", name))
    conf.real_time_html = 1;

  /* TLS/SSL certificate */
  if (!strcmp ("ssl-cert", name))
    conf.sslcert = oarg;

  /* TLS/SSL private key */
  if (!strcmp ("ssl-key", name))
    conf.sslkey = oarg;

  /* URL to which the WebSocket server responds. */
  if (!strcmp ("ws-url", name))
    conf.ws_url = oarg;

  /* FILE OPTIONS
   * ========================= */
  /* invalid requests */
  if (!strcmp ("invalid-requests", name)) {
    conf.invalid_requests_log = oarg;
    invalid_log_open (conf.invalid_requests_log);
  }

  /* output file */
  if (!strcmp ("output", name))
    set_array_opt (oarg, conf.output_formats, &conf.output_format_idx,
                   MAX_OUTFORMATS);

  /* PARSE OPTIONS
   * ========================= */
  /* 444 as 404 */
  if (!strcmp ("444-as-404", name))
    conf.code444_as_404 = 1;

  /* 4xx to unique count */
  if (!strcmp ("4xx-to-unique-count", name))
    conf.client_err_to_unique_count = 1;

  /* anonymize ip */
  if (!strcmp ("anonymize-ip", name))
    conf.anonymize_ip = 1;

  /* store accumulated time in tcb */
  if (!strcmp ("accumulated-time", name))
    conf.store_accumulated_time = 1;

  /* all static files */
  if (!strcmp ("all-static-files", name))
    conf.all_static_files = 1;

  /* crawlers only */
  if (!strcmp ("crawlers-only", name))
    conf.crawlers_only = 1;

  /* date specificity */
  if (!strcmp ("date-spec", name) && !strcmp (oarg, "hr"))
    conf.date_spec_hr = 1;

  /* double decode */
  if (!strcmp ("double-decode", name))
    conf.double_decode = 1;

  /* enable panel */
  if (!strcmp ("enable-panel", name))
    set_array_opt (oarg, conf.enable_panels, &conf.enable_panel_idx,
                   TOTAL_MODULES);

  /* hour specificity */
  if (!strcmp ("hour-spec", name) && !strcmp (oarg, "min"))
    conf.hour_spec_min = 1;

  /* ignore crawlers */
  if (!strcmp ("ignore-crawlers", name))
    conf.ignore_crawlers = 1;

  /* ignore panel */
  if (!strcmp ("ignore-panel", name))
    set_array_opt (oarg, conf.ignore_panels, &conf.ignore_panel_idx,
                   TOTAL_MODULES);

  /* ignore referer */
  if (!strcmp ("ignore-referer", name))
    set_array_opt (oarg, conf.ignore_referers, &conf.ignore_referer_idx,
                   MAX_IGNORE_REF);

  /* client IP validation */
  if (!strcmp ("no-ip-validation", name))
    conf.no_ip_validation = 1;

  /* hide referer from report (e.g. within same site) */
  if (!strcmp ("hide-referer", name))
    set_array_opt (oarg, conf.hide_referers, &conf.hide_referer_idx,
                   MAX_IGNORE_REF);

  /* ignore status code */
  if (!strcmp ("ignore-status", name))
    set_array_opt (oarg, conf.ignore_status, &conf.ignore_status_idx,
                   MAX_IGNORE_STATUS);

  /* ignore static requests */
  if (!strcmp ("ignore-statics", name)) {
    if (!strcmp ("req", oarg))
      conf.ignore_statics = IGNORE_LEVEL_REQ;
    else if (!strcmp ("panel", oarg))
      conf.ignore_statics = IGNORE_LEVEL_PANEL;
    else
      LOG_DEBUG (("Invalid statics ignore option."));
  }

  /* number of line tests */
  if (!strcmp ("num-tests", name)) {
    char *sEnd;
    int tests = strtol (oarg, &sEnd, 10);
    if (oarg == sEnd || *sEnd != '\0' || errno == ERANGE)
      return;
    conf.num_tests = tests >= 0 ? tests : 0;
  }

  /* process and exit */
  if (!strcmp ("process-and-exit", name))
    conf.process_and_exit = 1;

  /* real os */
  if (!strcmp ("real-os", name))
    conf.real_os = 1;

  /* sort view */
  if (!strcmp ("sort-panel", name))
    set_array_opt (oarg, conf.sort_panels, &conf.sort_panel_idx, TOTAL_MODULES);

  /* static file */
  if (!strcmp ("static-file", name) && conf.static_file_idx < MAX_EXTENSIONS) {
    if (conf.static_file_max_len < strlen (oarg))
      conf.static_file_max_len = strlen (oarg);
    set_array_opt (oarg, conf.static_files, &conf.static_file_idx,
                   MAX_EXTENSIONS);
  }

  /* GEOIP OPTIONS
   * ========================= */
  /* specifies the path of the GeoIP City database file */
  if (!strcmp ("geoip-city-data", name) || !strcmp ("geoip-database", name))
    conf.geoip_database = oarg;

  /* BTREE OPTIONS
   * ========================= */
  /* keep database files */
  if (!strcmp ("keep-db-files", name))
    conf.keep_db_files = 1;

  /* load data from disk */
  if (!strcmp ("load-from-disk", name))
    conf.load_from_disk = 1;

  /* specifies the path of the database file */
  if (!strcmp ("db-path", name))
    conf.db_path = oarg;

  /* specifies the maximum number of leaf nodes to be cached */
  if (!strcmp ("cache-lcnum", name))
    conf.cache_lcnum = atoi (oarg);

  /* specifies the maximum number of non-leaf nodes to be cached */
  if (!strcmp ("cache-ncnum", name))
    conf.cache_ncnum = atoi (oarg);

  /* number of elements of the bucket array */
  if (!strcmp ("tune-bnum", name))
    conf.tune_bnum = atoi (oarg);

  /* number of members in each non-leaf page */
  if (!strcmp ("tune-nmemb", name))
    conf.tune_nmemb = atoi (oarg);

  /* number of members in each leaf page */
  if (!strcmp ("tune-lmemb", name))
    conf.tune_lmemb = atoi (oarg);

  /* set the size in bytes of the extra mapped memory */
  if (!strcmp ("xmmap", name))
    conf.xmmap = atoi (oarg);

  /* specifies that each page is compressed with X encoding */
  if (!strcmp ("compression", name)) {
#ifdef HAVE_ZLIB
    if (!strcmp ("zlib", oarg))
      conf.compression = TC_ZLIB;
#endif
#ifdef HAVE_BZ2
    if (!strcmp ("bz2", oarg))
      conf.compression = TC_BZ2;
#endif
  }

  /* default config file --dwf */
  if (!strcmp ("dcf", name)) {
    display_default_config_file ();
    exit (EXIT_SUCCESS);
  }
}