#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pool; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {int /*<<< orphan*/  bdb; } ;
typedef  TYPE_2__ base_fs_data_t ;
struct TYPE_10__ {int (* close ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ DB ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_WRAP (TYPE_1__*,char*,int) ; 
 int DB_INCOMPLETE ; 
 int DB_RUNRECOVERY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_psprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_panic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__set_panic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
cleanup_fs_db(svn_fs_t *fs, DB **db_ptr, const char *name)
{
  /* If the BDB environment is panicked, don't do anything, since
     attempting to close the database will fail anyway. */
  base_fs_data_t *bfd = fs->fsap_data;
  if (*db_ptr && !svn_fs_bdb__get_panic(bfd->bdb))
    {
      DB *db = *db_ptr;
      char *msg = apr_psprintf(fs->pool, "closing '%s' database", name);
      int db_err;

      *db_ptr = 0;
      db_err = db->close(db, 0);
      if (db_err == DB_RUNRECOVERY)
        {
          /* We can ignore DB_RUNRECOVERY errors from DB->close, but
             must set the panic flag in the environment baton.  The
             error will be propagated appropriately from
             svn_fs_bdb__close. */
          svn_fs_bdb__set_panic(bfd->bdb);
          db_err = 0;
        }

#if SVN_BDB_HAS_DB_INCOMPLETE
      /* We can ignore DB_INCOMPLETE on db->close and db->sync; it
       * just means someone else was using the db at the same time
       * we were.  See the Berkeley documentation at:
       * http://www.sleepycat.com/docs/ref/program/errorret.html#DB_INCOMPLETE
       * http://www.sleepycat.com/docs/api_c/db_close.html
       */
      if (db_err == DB_INCOMPLETE)
        db_err = 0;
#endif /* SVN_BDB_HAS_DB_INCOMPLETE */

      SVN_ERR(BDB_WRAP(fs, msg, db_err));
    }

  return SVN_NO_ERROR;
}