#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_9__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_2__ apr_proc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  APR_READ ; 
 int /*<<< orphan*/  APR_WRITE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SVN_NULL_DEVICE_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_proc_kill (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char const* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,char*,char const*,char*,...) ; 
 char* stringbuf_split_key (TYPE_1__*,char) ; 
 scalar_t__ svn_cstring_casecmp (char const*,char*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_io_file_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_start_cmd3 (TYPE_2__*,int /*<<< orphan*/ *,char const* const,char const* const*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_io_wait_for_cmd (TYPE_2__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
lsb_release(apr_pool_t *pool)
{
  static const char *const args[3] =
    {
      "/usr/bin/lsb_release",
      "--all",
      NULL
    };

  const char *distributor = NULL;
  const char *description = NULL;
  const char *release = NULL;
  const char *codename = NULL;

  apr_proc_t lsbproc;
  svn_stream_t *lsbinfo;
  svn_error_t *err;

  /* Run /usr/bin/lsb_release --all < /dev/null 2>/dev/null */
  {
    apr_file_t *stdin_handle;
    apr_file_t *stdout_handle;

    err = svn_io_file_open(&stdin_handle, SVN_NULL_DEVICE_NAME,
                           APR_READ, APR_OS_DEFAULT, pool);
    if (!err)
      err = svn_io_file_open(&stdout_handle, SVN_NULL_DEVICE_NAME,
                             APR_WRITE, APR_OS_DEFAULT, pool);
    if (!err)
      err = svn_io_start_cmd3(&lsbproc, NULL, args[0], args, NULL, FALSE,
                              FALSE, stdin_handle,
                              TRUE, NULL,
                              FALSE, stdout_handle,
                              pool);
    if (err)
      {
        svn_error_clear(err);
        return NULL;
      }
  }

  /* Parse the output and try to populate the  */
  lsbinfo = svn_stream_from_aprfile2(lsbproc.out, TRUE, pool);
  if (lsbinfo)
    {
      for (;;)
        {
          svn_boolean_t eof = FALSE;
          svn_stringbuf_t *line;
          const char *key;

          err = svn_stream_readline(lsbinfo, &line, "\n", &eof, pool);
          if (err || eof)
            break;

          key = stringbuf_split_key(line, ':');
          if (!key)
            continue;

          if (0 == svn_cstring_casecmp(key, "Distributor ID"))
            distributor = line->data;
          else if (0 == svn_cstring_casecmp(key, "Description"))
            description = line->data;
          else if (0 == svn_cstring_casecmp(key, "Release"))
            release = line->data;
          else if (0 == svn_cstring_casecmp(key, "Codename"))
            codename = line->data;
        }
      err = svn_error_compose_create(err,
                                     svn_stream_close(lsbinfo));
      if (err)
        {
          svn_error_clear(err);
          apr_proc_kill(&lsbproc, SIGKILL);
          return NULL;
        }
    }

  /* Reap the child process */
  err = svn_io_wait_for_cmd(&lsbproc, "", NULL, NULL, pool);
  if (err)
    {
      svn_error_clear(err);
      return NULL;
    }

  if (description)
    return apr_psprintf(pool, "%s%s%s%s", description,
                        (codename ? " (" : ""),
                        (codename ? codename : ""),
                        (codename ? ")" : ""));
  if (distributor)
    return apr_psprintf(pool, "%s%s%s%s%s%s", distributor,
                        (release ? " " : ""),
                        (release ? release : ""),
                        (codename ? " (" : ""),
                        (codename ? codename : ""),
                        (codename ? ")" : ""));

  return NULL;
}