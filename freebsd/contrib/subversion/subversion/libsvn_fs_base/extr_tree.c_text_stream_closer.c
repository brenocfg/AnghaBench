#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct text_baton_t {int /*<<< orphan*/  pool; TYPE_1__* root; int /*<<< orphan*/  file_stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct text_baton_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txn_body_fulltext_finalize_edits ; 

__attribute__((used)) static svn_error_t *
text_stream_closer(void *baton)
{
  struct text_baton_t *tb = baton;

  /* Close the internal-use stream.  ### This used to be inside of
     txn_body_fulltext_finalize_edits(), but that invoked a nested
     Berkeley DB transaction -- scandalous! */
  SVN_ERR(svn_stream_close(tb->file_stream));

  /* Need to tell fs that we're done sending text */
  return svn_fs_base__retry_txn(tb->root->fs,
                                txn_body_fulltext_finalize_edits, tb,
                                FALSE, tb->pool);
}