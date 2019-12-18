#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_35__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct TYPE_36__ {int cache_size; void* single_threaded; } ;
typedef  TYPE_2__ svn_cache_config_t ;
typedef  int svn_boolean_t ;
struct TYPE_37__ {char* root; int tunnel; char const* tunnel_user; int memory_cache_size; int zero_copy_limit; int error_check_interval; int max_request_size; int max_response_size; int /*<<< orphan*/ * logger; int /*<<< orphan*/  compression_level; int /*<<< orphan*/ * config_pool; int /*<<< orphan*/ * cfg; int /*<<< orphan*/ * base; int /*<<< orphan*/ * fs_config; void* vhost; void* read_only; int /*<<< orphan*/  username_case; } ;
typedef  TYPE_3__ serve_params_t ;
typedef  enum run_mode { ____Placeholder_run_mode } run_mode ;
typedef  enum connection_handling_mode { ____Placeholder_connection_handling_mode } connection_handling_mode ;
struct TYPE_38__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ connection_t ;
typedef  int apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_uint16_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_socket_t ;
struct TYPE_39__ {int /*<<< orphan*/  family; } ;
typedef  TYPE_5__ apr_sockaddr_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_proc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;
struct TYPE_40__ {int ind; } ;
typedef  TYPE_6__ apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPT_BACKLOG ; 
 scalar_t__ APR_FROM_OS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_INCHILD ; 
 int APR_INET ; 
 int /*<<< orphan*/  APR_INET6 ; 
 scalar_t__ APR_INPARENT ; 
 int /*<<< orphan*/  APR_IPV4_ADDR_OK ; 
 int /*<<< orphan*/  APR_IPV6_ADDR_OK ; 
 int /*<<< orphan*/  APR_PROC_DETACH_DAEMONIZE ; 
 int /*<<< orphan*/  APR_PROTO_TCP ; 
 int /*<<< orphan*/  APR_SO_REUSEADDR ; 
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  APR_UINT16_MAX ; 
 int APR_UNSPEC ; 
 int /*<<< orphan*/  CASE_ASIS ; 
 int CONNECTION_DEFAULT ; 
 int /*<<< orphan*/  ERROR_FAILED_SERVICE_CONTROLLER_CONNECT ; 
 int EXIT_FAILURE ; 
 void* FALSE ; 
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int MAX_REQUEST_SIZE ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
#define  SVNSERVE_OPT_BLOCK_READ 151 
#define  SVNSERVE_OPT_CACHE_FULLTEXTS 150 
#define  SVNSERVE_OPT_CACHE_NODEPROPS 149 
#define  SVNSERVE_OPT_CACHE_REVPROPS 148 
#define  SVNSERVE_OPT_CACHE_TXDELTAS 147 
#define  SVNSERVE_OPT_CLIENT_SPEED 146 
#define  SVNSERVE_OPT_CONFIG_FILE 145 
#define  SVNSERVE_OPT_FOREGROUND 144 
#define  SVNSERVE_OPT_LISTEN_HOST 143 
#define  SVNSERVE_OPT_LISTEN_PORT 142 
#define  SVNSERVE_OPT_LOG_FILE 141 
#define  SVNSERVE_OPT_MAX_REQUEST 140 
#define  SVNSERVE_OPT_MAX_RESPONSE 139 
#define  SVNSERVE_OPT_MAX_THREADS 138 
#define  SVNSERVE_OPT_MIN_THREADS 137 
#define  SVNSERVE_OPT_PID_FILE 136 
#define  SVNSERVE_OPT_SERVICE 135 
#define  SVNSERVE_OPT_SINGLE_CONN 134 
#define  SVNSERVE_OPT_TUNNEL_USER 133 
#define  SVNSERVE_OPT_VERSION 132 
#define  SVNSERVE_OPT_VIRTUAL_HOST 131 
 int /*<<< orphan*/  SVN_DELTA_COMPRESSION_LEVEL_DEFAULT ; 
 int /*<<< orphan*/  SVN_DELTA_COMPRESSION_LEVEL_MAX ; 
 int /*<<< orphan*/  SVN_DELTA_COMPRESSION_LEVEL_NONE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_BLOCK_READ ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_DELTAS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_FULLTEXTS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_NODEPROPS ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_CACHE_REVPROPS ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_SVN_PORT ; 
 int THREADPOOL_MAX_SIZE ; 
 int THREADPOOL_MIN_SIZE ; 
 int /*<<< orphan*/  THREADPOOL_THREAD_IDLE_LIMIT ; 
 void* TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  accept_connection (TYPE_4__**,int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_getopt_long (TYPE_6__*,int /*<<< orphan*/ ,int*,char const**) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_os_sock_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_proc_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ apr_proc_fork (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_sockaddr_info_get (TYPE_5__**,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_socket_bind (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  apr_socket_close (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_socket_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ apr_socket_listen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_socket_opt_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int apr_strtoi64 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_thread_pool_create (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_thread_pool_idle_wait_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_thread_pool_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_thread_pool_threshold_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  attach_connection (TYPE_4__*) ; 
 int /*<<< orphan*/  check_lib_versions () ; 
 int /*<<< orphan*/  close_connection (TYPE_4__*) ; 
#define  connection_mode_fork 130 
#define  connection_mode_single 129 
#define  connection_mode_thread 128 
 int /*<<< orphan*/  connection_pools ; 
 int /*<<< orphan*/  cyrus_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  help (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logger__create (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logger__create_for_stderr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logger__log_error (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redirect_stdout ; 
 int run_mode_daemon ; 
 int run_mode_inetd ; 
 int run_mode_listen_once ; 
 int run_mode_service ; 
 int run_mode_tunnel ; 
 int run_mode_unspecified ; 
 TYPE_1__* serve (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* serve_socket (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serve_thread ; 
 int /*<<< orphan*/  sigchld_handler ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_2__* svn_cache_config_get () ; 
 int /*<<< orphan*/  svn_cache_config_set (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_cmdline__getopt_init (TYPE_6__**,int,char const**,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_cmdline_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* svn_cmdline_fputs (char*,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  svn_cstring_atoui64 (int*,char const*) ; 
 TYPE_1__* svn_cstring_strtoui64 (int*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 void* svn_dirent_internal_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,TYPE_1__*,char*,char const*) ; 
 TYPE_1__* svn_error_wrap_apr (scalar_t__,char*) ; 
 int /*<<< orphan*/  svn_fs_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_handle_error2 (TYPE_1__*,int /*<<< orphan*/ ,void*,char*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_io_check_resolved_path (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_svn_create_conn5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__config_pool_create (int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__config_pool_get (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_authz_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_root_pools__create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_for_stdin2 (int /*<<< orphan*/ **,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_for_stdout (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_tristate__from_word (char const*) ; 
 int /*<<< orphan*/  svn_tristate_true ; 
 int /*<<< orphan*/  svn_utf_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svnserve__options ; 
 int /*<<< orphan*/ * threads ; 
 int /*<<< orphan*/  usage (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  version (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  winservice_running () ; 
 TYPE_1__* winservice_start () ; 
 int /*<<< orphan*/  winservice_svnserve_accept_socket ; 
 int /*<<< orphan*/  write_pid_file (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
sub_main(int *exit_code, int argc, const char *argv[], apr_pool_t *pool)
{
  enum run_mode run_mode = run_mode_unspecified;
  svn_boolean_t foreground = FALSE;
  apr_socket_t *sock;
  apr_sockaddr_t *sa;
  svn_error_t *err;
  apr_getopt_t *os;
  int opt;
  serve_params_t params;
  const char *arg;
  apr_status_t status;
#ifndef WIN32
  apr_proc_t proc;
#endif
  svn_boolean_t is_multi_threaded;
  enum connection_handling_mode handling_mode = CONNECTION_DEFAULT;
  svn_boolean_t cache_fulltexts = TRUE;
  svn_boolean_t cache_nodeprops = TRUE;
  svn_boolean_t cache_txdeltas = TRUE;
  svn_boolean_t cache_revprops = FALSE;
  svn_boolean_t use_block_read = FALSE;
  apr_uint16_t port = SVN_RA_SVN_PORT;
  const char *host = NULL;
  int family = APR_INET;
  apr_int32_t sockaddr_info_flags = 0;
#if APR_HAVE_IPV6
  svn_boolean_t prefer_v6 = FALSE;
#endif
  svn_boolean_t quiet = FALSE;
  svn_boolean_t is_version = FALSE;
  int mode_opt_count = 0;
  int handling_opt_count = 0;
  const char *config_filename = NULL;
  const char *pid_filename = NULL;
  const char *log_filename = NULL;
  svn_node_kind_t kind;
  apr_size_t min_thread_count = THREADPOOL_MIN_SIZE;
  apr_size_t max_thread_count = THREADPOOL_MAX_SIZE;
#ifdef SVN_HAVE_SASL
  SVN_ERR(cyrus_init(pool));
#endif

  /* Check library versions */
  SVN_ERR(check_lib_versions());

  /* Initialize the FS library. */
  SVN_ERR(svn_fs_initialize(pool));

  /* Initialize the efficient Authz support. */
  SVN_ERR(svn_repos_authz_initialize(pool));

  SVN_ERR(svn_cmdline__getopt_init(&os, argc, argv, pool));

  params.root = "/";
  params.tunnel = FALSE;
  params.tunnel_user = NULL;
  params.read_only = FALSE;
  params.base = NULL;
  params.cfg = NULL;
  params.compression_level = SVN_DELTA_COMPRESSION_LEVEL_DEFAULT;
  params.logger = NULL;
  params.config_pool = NULL;
  params.fs_config = NULL;
  params.vhost = FALSE;
  params.username_case = CASE_ASIS;
  params.memory_cache_size = (apr_uint64_t)-1;
  params.zero_copy_limit = 0;
  params.error_check_interval = 4096;
  params.max_request_size = MAX_REQUEST_SIZE * 0x100000;
  params.max_response_size = 0;

  while (1)
    {
      status = apr_getopt_long(os, svnserve__options, &opt, &arg);
      if (APR_STATUS_IS_EOF(status))
        break;
      if (status != APR_SUCCESS)
        {
          usage(argv[0], pool);
          *exit_code = EXIT_FAILURE;
          return SVN_NO_ERROR;
        }
      switch (opt)
        {
        case '6':
#if APR_HAVE_IPV6
          prefer_v6 = TRUE;
#endif
          /* ### Maybe error here if we don't have IPV6 support? */
          break;

        case 'h':
          help(pool);
          return SVN_NO_ERROR;

        case 'q':
          quiet = TRUE;
          break;

        case SVNSERVE_OPT_VERSION:
          is_version = TRUE;
          break;

        case 'd':
          if (run_mode != run_mode_daemon)
            {
              run_mode = run_mode_daemon;
              mode_opt_count++;
            }
          break;

        case SVNSERVE_OPT_FOREGROUND:
          foreground = TRUE;
          break;

        case SVNSERVE_OPT_SINGLE_CONN:
          handling_mode = connection_mode_single;
          handling_opt_count++;
          break;

        case 'i':
          if (run_mode != run_mode_inetd)
            {
              run_mode = run_mode_inetd;
              mode_opt_count++;
            }
          break;

        case SVNSERVE_OPT_LISTEN_PORT:
          {
            apr_uint64_t val;

            err = svn_cstring_strtoui64(&val, arg, 0, APR_UINT16_MAX, 10);
            if (err)
              return svn_error_createf(SVN_ERR_CL_ARG_PARSING_ERROR, err,
                                       _("Invalid port '%s'"), arg);
            port = (apr_uint16_t)val;
          }
          break;

        case SVNSERVE_OPT_LISTEN_HOST:
          host = arg;
          break;

        case 't':
          if (run_mode != run_mode_tunnel)
            {
              run_mode = run_mode_tunnel;
              mode_opt_count++;
            }
          break;

        case SVNSERVE_OPT_TUNNEL_USER:
          params.tunnel_user = arg;
          break;

        case 'X':
          if (run_mode != run_mode_listen_once)
            {
              run_mode = run_mode_listen_once;
              mode_opt_count++;
            }
          break;

        case 'r':
          SVN_ERR(svn_utf_cstring_to_utf8(&params.root, arg, pool));

          SVN_ERR(svn_io_check_resolved_path(params.root, &kind, pool));
          if (kind != svn_node_dir)
            {
              return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                       _("Root path '%s' does not exist "
                         "or is not a directory"), params.root);
            }

          params.root = svn_dirent_internal_style(params.root, pool);
          SVN_ERR(svn_dirent_get_absolute(&params.root, params.root, pool));
          break;

        case 'R':
          params.read_only = TRUE;
          break;

        case 'T':
          handling_mode = connection_mode_thread;
          handling_opt_count++;
          break;

        case 'c':
          params.compression_level = atoi(arg);
          if (params.compression_level < SVN_DELTA_COMPRESSION_LEVEL_NONE)
            params.compression_level = SVN_DELTA_COMPRESSION_LEVEL_NONE;
          if (params.compression_level > SVN_DELTA_COMPRESSION_LEVEL_MAX)
            params.compression_level = SVN_DELTA_COMPRESSION_LEVEL_MAX;
          break;

        case 'M':
          {
            apr_uint64_t sz_val;
            SVN_ERR(svn_cstring_atoui64(&sz_val, arg));

            params.memory_cache_size = 0x100000 * sz_val;
          }
          break;

        case SVNSERVE_OPT_CACHE_TXDELTAS:
          cache_txdeltas = svn_tristate__from_word(arg) == svn_tristate_true;
          break;

        case SVNSERVE_OPT_CACHE_FULLTEXTS:
          cache_fulltexts = svn_tristate__from_word(arg) == svn_tristate_true;
          break;

        case SVNSERVE_OPT_CACHE_REVPROPS:
          cache_revprops = svn_tristate__from_word(arg) == svn_tristate_true;
          break;

        case SVNSERVE_OPT_CACHE_NODEPROPS:
          cache_nodeprops = svn_tristate__from_word(arg) == svn_tristate_true;
          break;

        case SVNSERVE_OPT_BLOCK_READ:
          use_block_read = svn_tristate__from_word(arg) == svn_tristate_true;
          break;

        case SVNSERVE_OPT_CLIENT_SPEED:
          {
            apr_size_t bandwidth = (apr_size_t)apr_strtoi64(arg, NULL, 0);

            /* for slower clients, don't try anything fancy */
            if (bandwidth >= 1000)
              {
                /* block other clients for at most 1 ms (at full bandwidth).
                   Note that the send buffer is 16kB anyways. */
                params.zero_copy_limit = bandwidth * 120;

                /* check for aborted connections at the same rate */
                params.error_check_interval = bandwidth * 120;
              }
          }
          break;

        case SVNSERVE_OPT_MAX_REQUEST:
          params.max_request_size = 0x100000 * apr_strtoi64(arg, NULL, 0);
          break;

        case SVNSERVE_OPT_MAX_RESPONSE:
          params.max_response_size = 0x100000 * apr_strtoi64(arg, NULL, 0);
          break;

        case SVNSERVE_OPT_MIN_THREADS:
          min_thread_count = (apr_size_t)apr_strtoi64(arg, NULL, 0);
          break;

        case SVNSERVE_OPT_MAX_THREADS:
          max_thread_count = (apr_size_t)apr_strtoi64(arg, NULL, 0);
          break;

#ifdef WIN32
        case SVNSERVE_OPT_SERVICE:
          if (run_mode != run_mode_service)
            {
              run_mode = run_mode_service;
              mode_opt_count++;
            }
          break;
#endif

        case SVNSERVE_OPT_CONFIG_FILE:
          SVN_ERR(svn_utf_cstring_to_utf8(&config_filename, arg, pool));
          config_filename = svn_dirent_internal_style(config_filename, pool);
          SVN_ERR(svn_dirent_get_absolute(&config_filename, config_filename,
                                          pool));
          break;

        case SVNSERVE_OPT_PID_FILE:
          SVN_ERR(svn_utf_cstring_to_utf8(&pid_filename, arg, pool));
          pid_filename = svn_dirent_internal_style(pid_filename, pool);
          SVN_ERR(svn_dirent_get_absolute(&pid_filename, pid_filename, pool));
          break;

         case SVNSERVE_OPT_VIRTUAL_HOST:
           params.vhost = TRUE;
           break;

         case SVNSERVE_OPT_LOG_FILE:
          SVN_ERR(svn_utf_cstring_to_utf8(&log_filename, arg, pool));
          log_filename = svn_dirent_internal_style(log_filename, pool);
          SVN_ERR(svn_dirent_get_absolute(&log_filename, log_filename, pool));
          break;

        }
    }

  if (is_version)
    {
      SVN_ERR(version(quiet, pool));
      return SVN_NO_ERROR;
    }

  if (os->ind != argc)
    {
      usage(argv[0], pool);
      *exit_code = EXIT_FAILURE;
      return SVN_NO_ERROR;
    }

  if (mode_opt_count != 1)
    {
      svn_error_clear(svn_cmdline_fputs(
#ifdef WIN32
                      _("You must specify exactly one of -d, -i, -t, "
                        "--service or -X.\n"),
#else
                      _("You must specify exactly one of -d, -i, -t or -X.\n"),
#endif
                       stderr, pool));
      usage(argv[0], pool);
      *exit_code = EXIT_FAILURE;
      return SVN_NO_ERROR;
    }

  if (handling_opt_count > 1)
    {
      svn_error_clear(svn_cmdline_fputs(
                      _("You may only specify one of -T or --single-thread\n"),
                      stderr, pool));
      usage(argv[0], pool);
      *exit_code = EXIT_FAILURE;
      return SVN_NO_ERROR;
    }

  /* construct object pools */
  is_multi_threaded = handling_mode == connection_mode_thread;
  params.fs_config = apr_hash_make(pool);
  svn_hash_sets(params.fs_config, SVN_FS_CONFIG_FSFS_CACHE_DELTAS,
                cache_txdeltas ? "1" :"0");
  svn_hash_sets(params.fs_config, SVN_FS_CONFIG_FSFS_CACHE_FULLTEXTS,
                cache_fulltexts ? "1" :"0");
  svn_hash_sets(params.fs_config, SVN_FS_CONFIG_FSFS_CACHE_NODEPROPS,
                cache_nodeprops ? "1" :"0");
  svn_hash_sets(params.fs_config, SVN_FS_CONFIG_FSFS_CACHE_REVPROPS,
                cache_revprops ? "2" :"0");
  svn_hash_sets(params.fs_config, SVN_FS_CONFIG_FSFS_BLOCK_READ,
                use_block_read ? "1" :"0");

  SVN_ERR(svn_repos__config_pool_create(&params.config_pool,
                                        is_multi_threaded,
                                        pool));

  /* If a configuration file is specified, load it and any referenced
   * password and authorization files. */
  if (config_filename)
    {
      params.base = svn_dirent_dirname(config_filename, pool);

      SVN_ERR(svn_repos__config_pool_get(&params.cfg,
                                         params.config_pool,
                                         config_filename,
                                         TRUE, /* must_exist */
                                         NULL,
                                         pool));
    }

  if (log_filename)
    SVN_ERR(logger__create(&params.logger, log_filename, pool));
  else if (run_mode == run_mode_listen_once)
    SVN_ERR(logger__create_for_stderr(&params.logger, pool));

  if (params.tunnel_user && run_mode != run_mode_tunnel)
    {
      return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
               _("Option --tunnel-user is only valid in tunnel mode"));
    }

  if (run_mode == run_mode_inetd || run_mode == run_mode_tunnel)
    {
      apr_pool_t *connection_pool;
      svn_ra_svn_conn_t *conn;
      svn_stream_t *stdin_stream;
      svn_stream_t *stdout_stream;

      params.tunnel = (run_mode == run_mode_tunnel);
      apr_pool_cleanup_register(pool, pool, apr_pool_cleanup_null,
                                redirect_stdout);

      /* We are an interactive server, i.e. can't use APR buffering on
       * stdin. */
      SVN_ERR(svn_stream_for_stdin2(&stdin_stream, FALSE, pool));
      SVN_ERR(svn_stream_for_stdout(&stdout_stream, pool));

      /* Use a subpool for the connection to ensure that if SASL is used
       * the pool cleanup handlers that call sasl_dispose() (connection_pool)
       * and sasl_done() (pool) are run in the right order. See issue #3664. */
      connection_pool = svn_pool_create(pool);
      conn = svn_ra_svn_create_conn5(NULL, stdin_stream, stdout_stream,
                                     params.compression_level,
                                     params.zero_copy_limit,
                                     params.error_check_interval,
                                     params.max_request_size,
                                     params.max_response_size,
                                     connection_pool);
      err = serve(conn, &params, connection_pool);
      svn_pool_destroy(connection_pool);

      return err;
    }

#ifdef WIN32
  /* If svnserve needs to run as a Win32 service, then we need to
     coordinate with the Service Control Manager (SCM) before
     continuing.  This function call registers the svnserve.exe
     process with the SCM, waits for the "start" command from the SCM
     (which will come very quickly), and confirms that those steps
     succeeded.

     After this call succeeds, the service is free to run.  At some
     point in the future, the SCM will send a message to the service,
     requesting that it stop.  This is translated into a call to
     winservice_notify_stop().  The service is then responsible for
     cleanly terminating.

     We need to do this before actually starting the service logic
     (opening files, sockets, etc.) because the SCM wants you to
     connect *first*, then do your service-specific logic.  If the
     service process takes too long to connect to the SCM, then the
     SCM will decide that the service is busted, and will give up on
     it.
     */
  if (run_mode == run_mode_service)
    {
      err = winservice_start();
      if (err)
        {
          svn_handle_error2(err, stderr, FALSE, "svnserve: ");

          /* This is the most common error.  It means the user started
             svnserve from a shell, and specified the --service
             argument.  svnserve cannot be started, as a service, in
             this way.  The --service argument is valid only valid if
             svnserve is started by the SCM. */
          if (err->apr_err ==
              APR_FROM_OS_ERROR(ERROR_FAILED_SERVICE_CONTROLLER_CONNECT))
            {
              svn_error_clear(svn_cmdline_fprintf(stderr, pool,
                  _("svnserve: The --service flag is only valid if the"
                    " process is started by the Service Control Manager.\n")));
            }

          svn_error_clear(err);
          *exit_code = EXIT_FAILURE;
          return SVN_NO_ERROR;
        }

      /* The service is now in the "starting" state.  Before the SCM will
         consider the service "started", this thread must call the
         winservice_running() function. */
    }
#endif /* WIN32 */

  /* Make sure we have IPV6 support first before giving apr_sockaddr_info_get
     APR_UNSPEC, because it may give us back an IPV6 address even if we can't
     create IPV6 sockets. */

#if APR_HAVE_IPV6
#ifdef MAX_SECS_TO_LINGER
  /* ### old APR interface */
  status = apr_socket_create(&sock, APR_INET6, SOCK_STREAM, pool);
#else
  status = apr_socket_create(&sock, APR_INET6, SOCK_STREAM, APR_PROTO_TCP,
                             pool);
#endif
  if (status == 0)
    {
      apr_socket_close(sock);
      family = APR_UNSPEC;

      if (prefer_v6)
        {
          if (host == NULL)
            host = "::";
          sockaddr_info_flags = APR_IPV6_ADDR_OK;
        }
      else
        {
          if (host == NULL)
            host = "0.0.0.0";
          sockaddr_info_flags = APR_IPV4_ADDR_OK;
        }
    }
#endif

  status = apr_sockaddr_info_get(&sa, host, family, port,
                                 sockaddr_info_flags, pool);
  if (status)
    {
      return svn_error_wrap_apr(status, _("Can't get address info"));
    }


#ifdef MAX_SECS_TO_LINGER
  /* ### old APR interface */
  status = apr_socket_create(&sock, sa->family, SOCK_STREAM, pool);
#else
  status = apr_socket_create(&sock, sa->family, SOCK_STREAM, APR_PROTO_TCP,
                             pool);
#endif
  if (status)
    {
      return svn_error_wrap_apr(status, _("Can't create server socket"));
    }

  /* Prevents "socket in use" errors when server is killed and quickly
   * restarted. */
  status = apr_socket_opt_set(sock, APR_SO_REUSEADDR, 1);
  if (status)
    {
      return svn_error_wrap_apr(status, _("Can't set options on server socket"));
    }

  status = apr_socket_bind(sock, sa);
  if (status)
    {
      return svn_error_wrap_apr(status, _("Can't bind server socket"));
    }

  status = apr_socket_listen(sock, ACCEPT_BACKLOG);
  if (status)
    {
      return svn_error_wrap_apr(status, _("Can't listen on server socket"));
    }

#if APR_HAS_FORK
  if (run_mode != run_mode_listen_once && !foreground)
    /* ### ignoring errors... */
    apr_proc_detach(APR_PROC_DETACH_DAEMONIZE);

  apr_signal(SIGCHLD, sigchld_handler);
#endif

#ifdef SIGPIPE
  /* Disable SIGPIPE generation for the platforms that have it. */
  apr_signal(SIGPIPE, SIG_IGN);
#endif

#ifdef SIGXFSZ
  /* Disable SIGXFSZ generation for the platforms that have it, otherwise
   * working with large files when compiled against an APR that doesn't have
   * large file support will crash the program, which is uncool. */
  apr_signal(SIGXFSZ, SIG_IGN);
#endif

  if (pid_filename)
    SVN_ERR(write_pid_file(pid_filename, pool));

#ifdef WIN32
  status = apr_os_sock_get(&winservice_svnserve_accept_socket, sock);
  if (status)
    winservice_svnserve_accept_socket = INVALID_SOCKET;

  /* At this point, the service is "running".  Notify the SCM. */
  if (run_mode == run_mode_service)
    winservice_running();
#endif

  /* Configure FS caches for maximum efficiency with svnserve.
   * For pre-forked (i.e. multi-processed) mode of operation,
   * keep the per-process caches smaller than the default.
   * Also, apply the respective command line parameters, if given. */
  {
    svn_cache_config_t settings = *svn_cache_config_get();

    if (params.memory_cache_size != -1)
      settings.cache_size = params.memory_cache_size;

    settings.single_threaded = TRUE;
    if (handling_mode == connection_mode_thread)
      {
#if APR_HAS_THREADS
        settings.single_threaded = FALSE;
#else
        /* No requests will be processed at all
         * (see "switch (handling_mode)" code further down).
         * But if they were, some other synchronization code
         * would need to take care of securing integrity of
         * APR-based structures. That would include our caches.
         */
#endif
      }

    svn_cache_config_set(&settings);
  }

#if APR_HAS_THREADS
  SVN_ERR(svn_root_pools__create(&connection_pools));

  if (handling_mode == connection_mode_thread)
    {
      /* create the thread pool with a valid range of threads */
      if (max_thread_count < 1)
        max_thread_count = 1;
      if (min_thread_count > max_thread_count)
        min_thread_count = max_thread_count;

      status = apr_thread_pool_create(&threads,
                                      min_thread_count,
                                      max_thread_count,
                                      pool);
      if (status)
        {
          return svn_error_wrap_apr(status, _("Can't create thread pool"));
        }

      /* let idle threads linger for a while in case more requests are
         coming in */
      apr_thread_pool_idle_wait_set(threads, THREADPOOL_THREAD_IDLE_LIMIT);

      /* don't queue requests unless we reached the worker thread limit */
      apr_thread_pool_threshold_set(threads, 0);
    }
  else
    {
      threads = NULL;
    }
#endif

  while (1)
    {
      connection_t *connection = NULL;
      SVN_ERR(accept_connection(&connection, sock, &params, handling_mode,
                                pool));
      if (run_mode == run_mode_listen_once)
        {
          err = serve_socket(connection, connection->pool);
          close_connection(connection);
          return err;
        }

      switch (handling_mode)
        {
        case connection_mode_fork:
#if APR_HAS_FORK
          status = apr_proc_fork(&proc, connection->pool);
          if (status == APR_INCHILD)
            {
              /* the child would't listen to the main server's socket */
              apr_socket_close(sock);

              /* serve_socket() logs any error it returns, so ignore it. */
              svn_error_clear(serve_socket(connection, connection->pool));
              close_connection(connection);
              return SVN_NO_ERROR;
            }
          else if (status != APR_INPARENT)
            {
              err = svn_error_wrap_apr(status, "apr_proc_fork");
              logger__log_error(params.logger, err, NULL, NULL);
              svn_error_clear(err);
            }
#endif
          break;

        case connection_mode_thread:
          /* Create a detached thread for each connection.  That's not a
             particularly sophisticated strategy for a threaded server, it's
             little different from forking one process per connection. */
#if APR_HAS_THREADS
          attach_connection(connection);

          status = apr_thread_pool_push(threads, serve_thread, connection,
                                        0, NULL);
          if (status)
            {
              return svn_error_wrap_apr(status, _("Can't push task"));
            }
#endif
          break;

        case connection_mode_single:
          /* Serve one connection at a time. */
          /* serve_socket() logs any error it returns, so ignore it. */
          svn_error_clear(serve_socket(connection, connection->pool));
        }

      close_connection(connection);
    }

  /* NOTREACHED */
}