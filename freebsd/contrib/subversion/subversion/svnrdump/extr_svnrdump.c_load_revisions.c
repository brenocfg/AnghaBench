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
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  check_cancel ; 
 int /*<<< orphan*/  svn_rdump__load_dumpstream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_for_stdin2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
load_revisions(svn_ra_session_t *session,
               svn_ra_session_t *aux_session,
               const char *dumpfile,
               svn_boolean_t quiet,
               apr_hash_t *skip_revprops,
               apr_pool_t *pool)
{
  svn_stream_t *output_stream;

  if (dumpfile)
    {
      SVN_ERR(svn_stream_open_readonly(&output_stream, dumpfile, pool, pool));
    }
  else
    {
      SVN_ERR(svn_stream_for_stdin2(&output_stream, TRUE, pool));
    }

  SVN_ERR(svn_rdump__load_dumpstream(output_stream, session, aux_session,
                                     quiet, skip_revprops,
                                     check_cancel, NULL, pool));

  return SVN_NO_ERROR;
}