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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {int /*<<< orphan*/  txn_root; scalar_t__ skipped; } ;
struct node_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  result_checksum; int /*<<< orphan*/  path; struct revision_baton* rb; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_checksum_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_apply_text (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
set_fulltext(svn_stream_t **stream,
             void *node_baton)
{
  struct node_baton *nb = node_baton;
  struct revision_baton *rb = nb->rb;

  /* If we're skipping this revision, we're done here. */
  if (rb->skipped)
    {
      *stream = NULL;
      return SVN_NO_ERROR;
    }

  return svn_fs_apply_text(stream,
                           rb->txn_root, nb->path,
                           svn_checksum_to_cstring(nb->result_checksum,
                                                   nb->pool),
                           nb->pool);
}