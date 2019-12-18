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
struct rep_read_baton {int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  fs; scalar_t__ trail; } ;
struct read_rep_args {char* buf; int /*<<< orphan*/ * len; struct rep_read_baton* rb; } ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct read_rep_args*,scalar_t__),struct read_rep_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txn_body_read_rep (struct read_rep_args*,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
rep_read_contents(void *baton, char *buf, apr_size_t *len)
{
  struct rep_read_baton *rb = baton;
  struct read_rep_args args;

  /* Clear the scratch pool of the results of previous invocations. */
  svn_pool_clear(rb->scratch_pool);

  args.rb = rb;
  args.buf = buf;
  args.len = len;

  /* If we got a trail, use it; else make one. */
  if (rb->trail)
    SVN_ERR(txn_body_read_rep(&args, rb->trail));
  else
    {
      /* In the case of reading from the db, any returned data should
         live in our pre-allocated buffer, so the whole operation can
         happen within a single malloc/free cycle.  This prevents us
         from creating millions of unnecessary trail subpools when
         reading a big file.  */
      SVN_ERR(svn_fs_base__retry_txn(rb->fs,
                                     txn_body_read_rep,
                                     &args,
                                     TRUE,
                                     rb->scratch_pool));
    }
  return SVN_NO_ERROR;
}