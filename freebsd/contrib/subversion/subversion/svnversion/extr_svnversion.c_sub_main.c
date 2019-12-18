#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {char* min_rev; char* max_rev; scalar_t__ sparse_checkout; scalar_t__ switched; scalar_t__ modified; } ;
typedef  TYPE_1__ svn_wc_revision_status_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_28__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_29__ {int interleave; int ind; char** argv; } ;
typedef  TYPE_3__ apr_getopt_t ;
struct TYPE_30__ {char* member_0; char member_1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_4__ apr_getopt_option_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 int EXIT_FAILURE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
#define  SVNVERSION_OPT_VERSION 128 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (char*) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 char* _ (char*) ; 
 scalar_t__ apr_getopt_long (TYPE_3__*,TYPE_4__ const*,int*,char const**) ; 
 TYPE_2__* check_lib_versions () ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  help (TYPE_4__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 TYPE_2__* svn_cmdline__getopt_init (TYPE_3__**,int,char const**,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_cmdline_fputs (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_cmdline_printf (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_2__* svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_io_check_special_path (char const*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 TYPE_2__* svn_opt__arg_canonicalize_path (char const**,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_utf_cstring_to_utf8 (char const**,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc_context_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc_revision_status2 (TYPE_1__**,int /*<<< orphan*/ *,char const*,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc_set_adm_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ *) ; 
 TYPE_2__* version (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
sub_main(int *exit_code, int argc, const char *argv[], apr_pool_t *pool)
{
  const char *wc_path, *trail_url;
  const char *local_abspath;
  svn_wc_revision_status_t *res;
  svn_boolean_t no_newline = FALSE, committed = FALSE;
  svn_error_t *err;
  apr_getopt_t *os;
  svn_wc_context_t *wc_ctx;
  svn_boolean_t quiet = FALSE;
  svn_boolean_t is_version = FALSE;
  const apr_getopt_option_t options[] =
    {
      {"no-newline", 'n', 0, N_("do not output the trailing newline")},
      {"committed",  'c', 0, N_("last changed rather than current revisions")},
      {"help", 'h', 0, N_("display this help")},
      {"version", SVNVERSION_OPT_VERSION, 0,
       N_("show program version information")},
      {"quiet",         'q', 0,
       N_("no progress (only errors) to stderr")},
      {0,             0,  0,  0}
    };

  /* Check library versions */
  SVN_ERR(check_lib_versions());

#if defined(WIN32) || defined(__CYGWIN__)
  /* Set the working copy administrative directory name. */
  if (getenv("SVN_ASP_DOT_NET_HACK"))
    {
      SVN_ERR(svn_wc_set_adm_dir("_svn", pool));
    }
#endif

  SVN_ERR(svn_cmdline__getopt_init(&os, argc, argv, pool));

  os->interleave = 1;
  while (1)
    {
      int opt;
      const char *arg;
      apr_status_t status = apr_getopt_long(os, options, &opt, &arg);
      if (APR_STATUS_IS_EOF(status))
        break;
      if (status != APR_SUCCESS)
        {
          *exit_code = EXIT_FAILURE;
          usage(pool);
          return SVN_NO_ERROR;
        }

      switch (opt)
        {
        case 'n':
          no_newline = TRUE;
          break;
        case 'c':
          committed = TRUE;
          break;
        case 'q':
          quiet = TRUE;
          break;
        case 'h':
          help(options, pool);
          return SVN_NO_ERROR;
        case SVNVERSION_OPT_VERSION:
          is_version = TRUE;
          break;
        default:
          *exit_code = EXIT_FAILURE;
          usage(pool);
          return SVN_NO_ERROR;
        }
    }

  if (is_version)
    {
      SVN_ERR(version(quiet, pool));
      return SVN_NO_ERROR;
    }
  if (os->ind > argc || os->ind < argc - 2)
    {
      *exit_code = EXIT_FAILURE;
      usage(pool);
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_utf_cstring_to_utf8(&wc_path,
                                  (os->ind < argc) ? os->argv[os->ind] : ".",
                                  pool));

  SVN_ERR(svn_opt__arg_canonicalize_path(&wc_path, wc_path, pool));
  SVN_ERR(svn_dirent_get_absolute(&local_abspath, wc_path, pool));
  SVN_ERR(svn_wc_context_create(&wc_ctx, NULL, pool, pool));

  if (os->ind+1 < argc)
    SVN_ERR(svn_utf_cstring_to_utf8(&trail_url, os->argv[os->ind+1], pool));
  else
    trail_url = NULL;

  err = svn_wc_revision_status2(&res, wc_ctx, local_abspath, trail_url,
                                committed, NULL, NULL, pool, pool);

  if (err && (err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND
              || err->apr_err == SVN_ERR_WC_NOT_WORKING_COPY))
    {
      svn_node_kind_t kind;
      svn_boolean_t special;

      svn_error_clear(err);

      SVN_ERR(svn_io_check_special_path(local_abspath, &kind, &special, pool));

      if (special)
        SVN_ERR(svn_cmdline_printf(pool, _("Unversioned symlink%s"),
                                   no_newline ? "" : "\n"));
      else if (kind == svn_node_dir)
        SVN_ERR(svn_cmdline_printf(pool, _("Unversioned directory%s"),
                                   no_newline ? "" : "\n"));
      else if (kind == svn_node_file)
        SVN_ERR(svn_cmdline_printf(pool, _("Unversioned file%s"),
                                   no_newline ? "" : "\n"));
      else
        {
          SVN_ERR(svn_cmdline_fprintf(stderr, pool,
                                      kind == svn_node_none
                                       ? _("'%s' doesn't exist\n")
                                       : _("'%s' is of unknown type\n"),
                                      svn_dirent_local_style(local_abspath,
                                                             pool)));
          *exit_code = EXIT_FAILURE;
          return SVN_NO_ERROR;
        }
      return SVN_NO_ERROR;
    }

  SVN_ERR(err);

  if (! SVN_IS_VALID_REVNUM(res->min_rev))
    {
      /* Local uncommitted modifications, no revision info was found. */
      SVN_ERR(svn_cmdline_printf(pool, _("Uncommitted local addition, "
                                         "copy or move%s"),
                                 no_newline ? "" : "\n"));
      return SVN_NO_ERROR;
    }

  /* Build compact '123[:456]M?S?' string. */
  SVN_ERR(svn_cmdline_printf(pool, "%ld", res->min_rev));
  if (res->min_rev != res->max_rev)
    SVN_ERR(svn_cmdline_printf(pool, ":%ld", res->max_rev));
  if (res->modified)
    SVN_ERR(svn_cmdline_fputs("M", stdout, pool));
  if (res->switched)
    SVN_ERR(svn_cmdline_fputs("S", stdout, pool));
  if (res->sparse_checkout)
    SVN_ERR(svn_cmdline_fputs("P", stdout, pool));

  if (! no_newline)
    SVN_ERR(svn_cmdline_fputs("\n", stdout, pool));

  return SVN_NO_ERROR;
}