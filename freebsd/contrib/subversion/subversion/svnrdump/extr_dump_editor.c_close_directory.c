#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct dir_baton {int /*<<< orphan*/  deleted_entries; TYPE_1__* eb; int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/  headers; scalar_t__ dump_props; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_3__ {int /*<<< orphan*/  stream; struct dir_baton* pending_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_node (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,struct dir_baton*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_node_delete (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_pending_dir (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_action_change ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static svn_error_t *
close_directory(void *dir_baton,
                apr_pool_t *pool)
{
  struct dir_baton *db = dir_baton;
  apr_hash_index_t *hi;
  svn_boolean_t this_pending;

  /* Remember if this directory is the one currently pending. */
  this_pending = (db->eb->pending_db == db);

  SVN_ERR(dump_pending_dir(db->eb, pool));

  /* If this directory was pending, then dump_pending() should have
     taken care of all the props and such.  Of course, the only way
     that would be the case is if this directory was added/replaced.

     Otherwise, if stuff for this directory has already been written
     out (at some point in the past, prior to our handling other
     nodes), we might need to generate a second "change" record just
     to carry the information we've since learned about the
     directory. */
  if ((! this_pending) && (db->dump_props))
    {
      SVN_ERR(dump_node(&db->headers,
                        db->eb, db->repos_relpath, db, NULL,
                        svn_node_action_change, FALSE,
                        NULL, SVN_INVALID_REVNUM, pool));
      db->eb->pending_db = db;
      SVN_ERR(dump_pending_dir(db->eb, pool));
    }

  /* Dump the deleted directory entries */
  for (hi = apr_hash_first(pool, db->deleted_entries); hi;
       hi = apr_hash_next(hi))
    {
      const char *path = apr_hash_this_key(hi);

      SVN_ERR(dump_node_delete(db->eb->stream, path, pool));
      /* This deletion record is complete -- write an extra newline */
      SVN_ERR(svn_stream_puts(db->eb->stream, "\n"));
    }

  /* ### should be unnecessary */
  apr_hash_clear(db->deleted_entries);

  return SVN_NO_ERROR;
}