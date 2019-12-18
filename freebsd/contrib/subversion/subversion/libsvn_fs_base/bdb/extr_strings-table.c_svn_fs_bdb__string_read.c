#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int32_t ;
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {char* data; int flags; scalar_t__ size; void* ulen; void* dlen; void* doff; } ;
typedef  TYPE_1__ DBT ;
typedef  int /*<<< orphan*/  DBC ;

/* Variables and functions */
 int /*<<< orphan*/ * BDB_WRAP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DB_CURRENT ; 
 int DB_DBT_PARTIAL ; 
 int DB_DBT_USERMEM ; 
 int DB_NOTFOUND ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int get_next_length (scalar_t__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * locate_key (scalar_t__*,int /*<<< orphan*/ **,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int svn_bdb_dbc_close (int /*<<< orphan*/ *) ; 
 int svn_bdb_dbc_get (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__clear_dbt (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_base__str_to_dbt (TYPE_1__*,char const*) ; 

svn_error_t *
svn_fs_bdb__string_read(svn_fs_t *fs,
                        const char *key,
                        char *buf,
                        svn_filesize_t offset,
                        apr_size_t *len,
                        trail_t *trail,
                        apr_pool_t *pool)
{
  int db_err;
  DBT query, result;
  DBC *cursor;
  apr_size_t length, bytes_read = 0;

  svn_fs_base__str_to_dbt(&query, key);

  SVN_ERR(locate_key(&length, &cursor, &query, fs, trail, pool));

  /* Seek through the records for this key, trying to find the record that
     includes OFFSET. Note that we don't require reading from more than
     one record since we're allowed to return partial reads.  */
  while (length <= offset)
    {
      offset -= length;

      /* Remember, if any error happens, our cursor has been closed
         for us. */
      db_err = get_next_length(&length, cursor, &query);

      /* No more records? They tried to read past the end. */
      if (db_err == DB_NOTFOUND)
        {
          *len = 0;
          return SVN_NO_ERROR;
        }
      if (db_err)
        return BDB_WRAP(fs, N_("reading string"), db_err);
    }

  /* The current record contains OFFSET. Fetch the contents now. Note that
     OFFSET has been moved to be relative to this record. The length could
     quite easily extend past this record, so we use DB_DBT_PARTIAL and
     read successive records until we've filled the request.  */
  while (1)
    {
      svn_fs_base__clear_dbt(&result);
      result.data = buf + bytes_read;
      result.ulen = (u_int32_t)(*len - bytes_read);
      result.doff = (u_int32_t)offset;
      result.dlen = result.ulen;
      result.flags |= (DB_DBT_USERMEM | DB_DBT_PARTIAL);
      db_err = svn_bdb_dbc_get(cursor, &query, &result, DB_CURRENT);
      if (db_err)
        {
          svn_bdb_dbc_close(cursor);
          return BDB_WRAP(fs, N_("reading string"), db_err);
        }

      bytes_read += result.size;
      if (bytes_read == *len)
        {
          /* Done with the cursor. */
          SVN_ERR(BDB_WRAP(fs, N_("closing string-reading cursor"),
                           svn_bdb_dbc_close(cursor)));
          break;
        }

      /* Remember, if any error happens, our cursor has been closed
         for us. */
      db_err = get_next_length(&length, cursor, &query);
      if (db_err == DB_NOTFOUND)
        break;
      if (db_err)
        return BDB_WRAP(fs, N_("reading string"), db_err);

      /* We'll be reading from the beginning of the next record */
      offset = 0;
    }

  *len = bytes_read;
  return SVN_NO_ERROR;
}