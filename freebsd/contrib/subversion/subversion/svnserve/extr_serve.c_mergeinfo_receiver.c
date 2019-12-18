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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  fs_path; } ;
typedef  TYPE_1__ mergeinfo_receiver_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  send_mergeinfo_starting_tuple (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_mergeinfo_to_string (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
mergeinfo_receiver(const char *path,
                   svn_mergeinfo_t mergeinfo,
                   void *baton,
                   apr_pool_t *scratch_pool)
{
  mergeinfo_receiver_baton_t *b = baton;
  svn_string_t *mergeinfo_string;

  /* Delay starting the response until we checked that the initial
     request went through.  We are at that point now b/c we've got
     the first results in. */
  SVN_ERR(send_mergeinfo_starting_tuple(b, scratch_pool));

  /* Adjust the path info and send the m/i. */
  path = svn_fspath__skip_ancestor(b->fs_path, path);
  SVN_ERR(svn_mergeinfo_to_string(&mergeinfo_string, mergeinfo,
                                  scratch_pool));
  SVN_ERR(svn_ra_svn__write_tuple(b->conn, scratch_pool, "cs", path,
                                  mergeinfo_string));

  return SVN_NO_ERROR;
}