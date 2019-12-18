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
typedef  int /*<<< orphan*/  svn_error_t ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  prefix_buf ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetConsoleCP () ; 
 scalar_t__ GetConsoleMode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetConsoleOutputCP () ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetUnhandledExceptionFilter (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  _CRTDBG_FILE_STDERR ; 
 int _CRTDBG_MODE_DEBUG ; 
 int _CRTDBG_MODE_FILE ; 
 int /*<<< orphan*/  _CRT_ASSERT ; 
 int /*<<< orphan*/  _CRT_ERROR ; 
 int /*<<< orphan*/  _CRT_WARN ; 
 int /*<<< orphan*/  _CrtSetReportFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CrtSetReportMode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  _OUT_TO_STDERR ; 
 scalar_t__ _isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_error_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ apr_initialize () ; 
 int /*<<< orphan*/  apr_snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  apr_strerror (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  apr_terminate ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int fstat (int,struct stat*) ; 
 char* getenv (char const*) ; 
 char* input_encoding ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* output_encoding ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* shortcut_stderr_to_console ; 
 void* shortcut_stdout_to_console ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  svn__unhandled_exception_filter ; 
 int /*<<< orphan*/ * svn_dso_initialize2 () ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_handle_error2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,char*) ; 
 int /*<<< orphan*/ * svn_nls_init () ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_utf_initialize2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
svn_cmdline_init(const char *progname, FILE *error_stream)
{
  apr_status_t status;
  apr_pool_t *pool;
  svn_error_t *err;
  char prefix_buf[64];  /* 64 is probably bigger than most program names */

#ifndef WIN32
  {
    struct stat st;

    /* The following makes sure that file descriptors 0 (stdin), 1
       (stdout) and 2 (stderr) will not be "reused", because if
       e.g. file descriptor 2 would be reused when opening a file, a
       write to stderr would write to that file and most likely
       corrupt it. */
    if ((fstat(0, &st) == -1 && open("/dev/null", O_RDONLY) == -1) ||
        (fstat(1, &st) == -1 && open("/dev/null", O_WRONLY) == -1) ||
        (fstat(2, &st) == -1 && open("/dev/null", O_WRONLY) == -1))
      {
        if (error_stream)
          fprintf(error_stream, "%s: error: cannot open '/dev/null'\n",
                  progname);
        return EXIT_FAILURE;
      }
  }
#endif

  /* Ignore any errors encountered while attempting to change stream
     buffering, as the streams should retain their default buffering
     modes. */
  if (error_stream)
    setvbuf(error_stream, NULL, _IONBF, 0);
#ifndef WIN32
  setvbuf(stdout, NULL, _IOLBF, 0);
#endif

#ifdef WIN32
#ifdef CMDLINE_USE_CUSTOM_ENCODING
  /* Initialize the input and output encodings. */
  {
    static char input_encoding_buffer[16];
    static char output_encoding_buffer[16];

    apr_snprintf(input_encoding_buffer, sizeof input_encoding_buffer,
                 "CP%u", (unsigned) GetConsoleCP());
    input_encoding = input_encoding_buffer;

    apr_snprintf(output_encoding_buffer, sizeof output_encoding_buffer,
                 "CP%u", (unsigned) GetConsoleOutputCP());
    output_encoding = output_encoding_buffer;
  }
#endif /* CMDLINE_USE_CUSTOM_ENCODING */

#ifdef SVN_USE_WIN32_CRASHHANDLER
  if (!getenv("SVN_CMDLINE_DISABLE_CRASH_HANDLER"))
    {
      /* Attach (but don't load) the crash handler */
      SetUnhandledExceptionFilter(svn__unhandled_exception_filter);

#if _MSC_VER >= 1400
      /* ### This should work for VC++ 2002 (=1300) and later */
      /* Show the abort message on STDERR instead of a dialog to allow
         scripts (e.g. our testsuite) to continue after an abort without
         user intervention. Allow overriding for easier debugging. */
      if (!getenv("SVN_CMDLINE_USE_DIALOG_FOR_ABORT"))
        {
          /* In release mode: Redirect abort() errors to stderr */
          _set_error_mode(_OUT_TO_STDERR);

          /* In _DEBUG mode: Redirect all debug output (E.g. assert() to stderr.
             (Ignored in release builds) */
          _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDERR);
          _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDERR);
          _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDERR);
          _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
          _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
          _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
        }
#endif /* _MSC_VER >= 1400 */
    }
#endif /* SVN_USE_WIN32_CRASHHANDLER */

#endif /* WIN32 */

  /* C programs default to the "C" locale. But because svn is supposed
     to be i18n-aware, it should inherit the default locale of its
     environment.  */
  if (!setlocale(LC_ALL, "")
      && !setlocale(LC_CTYPE, ""))
    {
      if (error_stream)
        {
          const char *env_vars[] = { "LC_ALL", "LC_CTYPE", "LANG", NULL };
          const char **env_var = &env_vars[0], *env_val = NULL;
          while (*env_var)
            {
              env_val = getenv(*env_var);
              if (env_val && env_val[0])
                break;
              ++env_var;
            }

          if (!*env_var)
            {
              /* Unlikely. Can setlocale fail if no env vars are set? */
              --env_var;
              env_val = "not set";
            }

          fprintf(error_stream,
                  "%s: warning: cannot set LC_CTYPE locale\n"
                  "%s: warning: environment variable %s is %s\n"
                  "%s: warning: please check that your locale name is correct\n",
                  progname, progname, *env_var, env_val, progname);
        }
    }

  /* Initialize the APR subsystem, and register an atexit() function
     to Uninitialize that subsystem at program exit. */
  status = apr_initialize();
  if (status)
    {
      if (error_stream)
        {
          char buf[1024];
          apr_strerror(status, buf, sizeof(buf) - 1);
          fprintf(error_stream,
                  "%s: error: cannot initialize APR: %s\n",
                  progname, buf);
        }
      return EXIT_FAILURE;
    }

  strncpy(prefix_buf, progname, sizeof(prefix_buf) - 3);
  prefix_buf[sizeof(prefix_buf) - 3] = '\0';
  strcat(prefix_buf, ": ");

  /* DSO pool must be created before any other pools used by the
     application so that pool cleanup doesn't unload DSOs too
     early. See docstring of svn_dso_initialize2(). */
  if ((err = svn_dso_initialize2()))
    {
      if (error_stream)
        svn_handle_error2(err, error_stream, TRUE, prefix_buf);

      svn_error_clear(err);
      return EXIT_FAILURE;
    }

  if (0 > atexit(apr_terminate))
    {
      if (error_stream)
        fprintf(error_stream,
                "%s: error: atexit registration failed\n",
                progname);
      return EXIT_FAILURE;
    }

  /* Create a pool for use by the UTF-8 routines.  It will be cleaned
     up by APR at exit time. */
  pool = svn_pool_create(NULL);
  svn_utf_initialize2(FALSE, pool);

  if ((err = svn_nls_init()))
    {
      if (error_stream)
        svn_handle_error2(err, error_stream, TRUE, prefix_buf);

      svn_error_clear(err);
      return EXIT_FAILURE;
    }

#ifdef USE_WIN32_CONSOLE_SHORTCUT
  if (_isatty(STDOUT_FILENO))
    {
      DWORD ignored;
      HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

       /* stdout is a char device handle, but is it the console? */
       if (GetConsoleMode(stdout_handle, &ignored))
        shortcut_stdout_to_console = TRUE;

       /* Don't close stdout_handle */
    }
  if (_isatty(STDERR_FILENO))
    {
      DWORD ignored;
      HANDLE stderr_handle = GetStdHandle(STD_ERROR_HANDLE);

       /* stderr is a char device handle, but is it the console? */
      if (GetConsoleMode(stderr_handle, &ignored))
          shortcut_stderr_to_console = TRUE;

      /* Don't close stderr_handle */
    }
#endif

  return EXIT_SUCCESS;
}