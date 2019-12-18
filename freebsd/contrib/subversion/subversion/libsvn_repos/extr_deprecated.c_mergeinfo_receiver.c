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
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  void* svn_mergeinfo_catalog_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_pool_get (void*) ; 
 int /*<<< orphan*/  apr_hash_set (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_mergeinfo_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
mergeinfo_receiver(const char *path,
                   svn_mergeinfo_t mergeinfo,
                   void *baton,
                   apr_pool_t *scratch_pool)
{
  svn_mergeinfo_catalog_t catalog = baton;
  apr_pool_t *result_pool = apr_hash_pool_get(catalog);
  apr_size_t len = strlen(path);

  apr_hash_set(catalog,
               apr_pstrmemdup(result_pool, path, len),
               len,
               svn_mergeinfo_dup(mergeinfo, result_pool));

  return SVN_NO_ERROR;
}