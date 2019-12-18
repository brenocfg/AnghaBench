#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  parents; } ;
typedef  TYPE_2__ svn_branch__history_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char*) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,...) ; 
 TYPE_2__* svn_branch__history_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_branch__rev_bid_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_readline (int /*<<< orphan*/ *,TYPE_1__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
history_parse(svn_branch__history_t **history_p,
              svn_stream_t *stream,
              apr_pool_t *result_pool,
              apr_pool_t *scratch_pool)
{
  svn_branch__history_t *history
    = svn_branch__history_create_empty(result_pool);
  svn_stringbuf_t *line;
  svn_boolean_t eof;
  int n;
  int num_parents;
  int i;

  /* Read a line */
  SVN_ERR(svn_stream_readline(stream, &line, "\n", &eof, scratch_pool));
  SVN_ERR_ASSERT(!eof);

  n = sscanf(line->data, "history: parents %d",
             &num_parents);
  SVN_ERR_ASSERT(n == 1);

  for (i = 0; i < num_parents; i++)
    {
      svn_revnum_t rev;
      char bid[100];

      SVN_ERR(svn_stream_readline(stream, &line, "\n", &eof, scratch_pool));
      SVN_ERR_ASSERT(!eof);

      n = sscanf(line->data, "parent: r%ld.%99s",
                 &rev, bid);
      SVN_ERR_ASSERT(n == 2);

      svn_hash_sets(history->parents,
                    apr_pstrdup(result_pool, bid),
                    svn_branch__rev_bid_create(rev, bid, result_pool));
    }

  if (history_p)
    *history_p = history;
  return SVN_NO_ERROR;
}