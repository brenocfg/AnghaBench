#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  data_key; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_6__ {scalar_t__ kind; int /*<<< orphan*/  fs; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FILE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__rep_contents_read_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

svn_error_t *
svn_fs_base__dag_get_contents(svn_stream_t **contents,
                              dag_node_t *file,
                              trail_t *trail,
                              apr_pool_t *pool)
{
  node_revision_t *noderev;

  /* Make sure our node is a file. */
  if (file->kind != svn_node_file)
    return svn_error_createf
      (SVN_ERR_FS_NOT_FILE, NULL,
       _("Attempted to get textual contents of a *non*-file node"));

  /* Go get a fresh node-revision for FILE. */
  SVN_ERR(svn_fs_bdb__get_node_revision(&noderev, file->fs, file->id,
                                        trail, pool));

  /* Our job is to _return_ a stream on the file's contents, so the
     stream has to be trail-independent.  Here, we pass NULL to tell
     the stream that we're not providing it a trail that lives across
     reads.  This means the stream will do each read in a one-off,
     temporary trail.  */
  return svn_fs_base__rep_contents_read_stream(contents, file->fs,
                                               noderev->data_key,
                                               FALSE, trail, pool);

  /* Note that we're not registering any `close' func, because there's
     nothing to cleanup outside of our trail.  When the trail is
     freed, the stream/baton will be too. */
}