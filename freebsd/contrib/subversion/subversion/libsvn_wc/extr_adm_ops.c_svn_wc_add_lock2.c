#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
struct TYPE_20__ {int /*<<< orphan*/  date; int /*<<< orphan*/  comment; int /*<<< orphan*/  owner; int /*<<< orphan*/  token; } ;
typedef  TYPE_2__ svn_wc__db_lock_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_21__ {int /*<<< orphan*/  creation_date; int /*<<< orphan*/  comment; int /*<<< orphan*/  owner; int /*<<< orphan*/  token; } ;
typedef  TYPE_3__ svn_lock_t ;
struct TYPE_22__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_NOT_FOUND ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 scalar_t__ SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 TYPE_4__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_NEEDS_LOCK ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 TYPE_4__* svn_io_set_file_read_write (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__db_lock_add (int /*<<< orphan*/ ,char const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__internal_propget (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_wc__write_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_add_lock2(svn_wc_context_t *wc_ctx,
                 const char *local_abspath,
                 const svn_lock_t *lock,
                 apr_pool_t *scratch_pool)
{
  svn_wc__db_lock_t db_lock;
  svn_error_t *err;
  const svn_string_t *needs_lock;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  SVN_ERR(svn_wc__write_check(wc_ctx->db,
                              svn_dirent_dirname(local_abspath, scratch_pool),
                              scratch_pool));

  db_lock.token = lock->token;
  db_lock.owner = lock->owner;
  db_lock.comment = lock->comment;
  db_lock.date = lock->creation_date;
  err = svn_wc__db_lock_add(wc_ctx->db, local_abspath, &db_lock, scratch_pool);
  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
        return svn_error_trace(err);

      /* Remap the error.  */
      svn_error_clear(err);
      return svn_error_createf(SVN_ERR_ENTRY_NOT_FOUND, NULL,
                               _("'%s' is not under version control"),
                               svn_dirent_local_style(local_abspath,
                                                      scratch_pool));
    }

  /* if svn:needs-lock is present, then make the file read-write. */
  err = svn_wc__internal_propget(&needs_lock, wc_ctx->db, local_abspath,
                                 SVN_PROP_NEEDS_LOCK, scratch_pool,
                                 scratch_pool);

  if (err && err->apr_err == SVN_ERR_WC_PATH_UNEXPECTED_STATUS)
    {
      /* The node has non wc representation (e.g. deleted), so
         we don't want to touch the in-wc file */
      svn_error_clear(err);
      return SVN_NO_ERROR;
    }
  SVN_ERR(err);

  if (needs_lock)
    SVN_ERR(svn_io_set_file_read_write(local_abspath, FALSE, scratch_pool));

  return SVN_NO_ERROR;
}