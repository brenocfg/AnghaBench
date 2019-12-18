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
typedef  int /*<<< orphan*/  svn_repos_notify_func_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct verify_mergeinfo_normalization_baton {char const* path; void* notify_baton; int /*<<< orphan*/  notify_func; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * normalized_paths; int /*<<< orphan*/ * paths; int /*<<< orphan*/ * result; int /*<<< orphan*/  normalize; } ;
struct filter_mergeinfo_paths_baton {char const* path; void* notify_baton; int /*<<< orphan*/  notify_func; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * normalized_paths; int /*<<< orphan*/ * paths; int /*<<< orphan*/ * result; int /*<<< orphan*/  normalize; } ;
struct extract_mergeinfo_paths_baton {char const* path; void* notify_baton; int /*<<< orphan*/  notify_func; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * normalized_paths; int /*<<< orphan*/ * paths; int /*<<< orphan*/ * result; int /*<<< orphan*/  normalize; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extract_mergeinfo_paths ; 
 int /*<<< orphan*/  filter_mergeinfo_paths ; 
 int /*<<< orphan*/  svn_iter_apr_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct verify_mergeinfo_normalization_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_membuf__create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_parse (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_mergeinfo_normalization ; 

__attribute__((used)) static svn_error_t *
check_mergeinfo_normalization(const char *path,
                              const char *new_mergeinfo,
                              const char *old_mergeinfo,
                              svn_repos_notify_func_t notify_func,
                              void *notify_baton,
                              apr_pool_t *pool)
{
  svn_mergeinfo_t mergeinfo;
  apr_hash_t *normalized_paths;
  apr_hash_t *added_paths;
  struct extract_mergeinfo_paths_baton extract_baton;
  struct verify_mergeinfo_normalization_baton verify_baton;

  SVN_ERR(svn_mergeinfo_parse(&mergeinfo, new_mergeinfo, pool));

  extract_baton.result = apr_hash_make(pool);
  extract_baton.normalize = FALSE;
  svn_membuf__create(&extract_baton.buffer, 0, pool);
  SVN_ERR(svn_iter_apr_hash(NULL, mergeinfo,
                            extract_mergeinfo_paths,
                            &extract_baton, pool));
  added_paths = extract_baton.result;

  if (old_mergeinfo)
    {
      struct filter_mergeinfo_paths_baton filter_baton;
      svn_mergeinfo_t oldinfo;

      extract_baton.result = apr_hash_make(pool);
      extract_baton.normalize = TRUE;
      SVN_ERR(svn_mergeinfo_parse(&oldinfo, old_mergeinfo, pool));
      SVN_ERR(svn_iter_apr_hash(NULL, oldinfo,
                                extract_mergeinfo_paths,
                                &extract_baton, pool));
      normalized_paths = extract_baton.result;

      filter_baton.paths = added_paths;
      SVN_ERR(svn_iter_apr_hash(NULL, oldinfo,
                                filter_mergeinfo_paths,
                                &filter_baton, pool));
    }
  else
      normalized_paths = apr_hash_make(pool);

  verify_baton.path = path;
  verify_baton.normalized_paths = normalized_paths;
  verify_baton.buffer = extract_baton.buffer;
  verify_baton.notify_func = notify_func;
  verify_baton.notify_baton = notify_baton;
  SVN_ERR(svn_iter_apr_hash(NULL, added_paths,
                            verify_mergeinfo_normalization,
                            &verify_baton, pool));

  return SVN_NO_ERROR;
}