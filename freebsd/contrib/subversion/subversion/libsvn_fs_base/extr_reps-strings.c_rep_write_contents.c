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
struct write_rep_args {char const* buf; int /*<<< orphan*/  len; struct rep_write_baton* wb; } ;
struct rep_write_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  fs; scalar_t__ trail; } ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct write_rep_args*,scalar_t__),struct write_rep_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txn_body_write_rep (struct write_rep_args*,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
rep_write_contents(void *baton,
                   const char *buf,
                   apr_size_t *len)
{
  struct rep_write_baton *wb = baton;
  struct write_rep_args args;

  /* We toss LEN's indirectness because if not all the bytes are
     written, it's an error, so we wouldn't be reporting anything back
     through *LEN anyway. */
  args.wb = wb;
  args.buf = buf;
  args.len = *len;

  /* If we got a trail, use it; else make one. */
  if (wb->trail)
    SVN_ERR(txn_body_write_rep(&args, wb->trail));
  else
    {
      /* In the case of simply writing the rep to the db, we're
         *certain* that there's no data coming back to us that needs
         to be preserved... so the whole operation can happen within a
         single malloc/free cycle.  This prevents us from creating
         millions of unnecessary trail subpools when writing a big
         file. */
      SVN_ERR(svn_fs_base__retry_txn(wb->fs,
                                     txn_body_write_rep,
                                     &args,
                                     TRUE,
                                     wb->pool));
    }

  return SVN_NO_ERROR;
}