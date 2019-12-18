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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct dump_edit_baton {struct dir_baton* pending_db; int /*<<< orphan*/  stream; } ;
struct dir_baton {scalar_t__ dump_props; int /*<<< orphan*/  deleted_props; int /*<<< orphan*/  props; int /*<<< orphan*/  headers; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_props_content (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__dump_node_record (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_puts (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static svn_error_t *
dump_pending_dir(struct dump_edit_baton *eb,
                 apr_pool_t *scratch_pool)
{
  struct dir_baton *db = eb->pending_db;
  svn_stringbuf_t *prop_content = NULL;

  if (! db)
    return SVN_NO_ERROR;

  /* Some pending properties to dump? */
  if (db->dump_props)
    {
      SVN_ERR(get_props_content(db->headers, &prop_content,
                                db->props, db->deleted_props,
                                scratch_pool, scratch_pool));
    }
  SVN_ERR(svn_repos__dump_node_record(eb->stream, db->headers, prop_content,
                                      FALSE, 0, FALSE /*content_length_always*/,
                                      scratch_pool));

  /* No text is going to be dumped. Write a couple of newlines and
       wait for the next node/ revision. */
  SVN_ERR(svn_stream_puts(eb->stream, "\n\n"));

  if (db->dump_props)
    {
      /* Cleanup so that data is never dumped twice. */
      apr_hash_clear(db->props);
      apr_hash_clear(db->deleted_props);
      db->dump_props = FALSE;
    }

  /* Anything that was pending is pending no longer. */
  eb->pending_db = NULL;

  return SVN_NO_ERROR;
}