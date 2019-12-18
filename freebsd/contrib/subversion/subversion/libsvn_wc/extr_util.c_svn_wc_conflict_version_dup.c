#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* repos_uuid; void* path_in_repos; void* repos_url; } ;
typedef  TYPE_1__ svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,void*) ; 

svn_wc_conflict_version_t *
svn_wc_conflict_version_dup(const svn_wc_conflict_version_t *version,
                            apr_pool_t *result_pool)
{

  svn_wc_conflict_version_t *new_version;

  if (version == NULL)
    return NULL;

  new_version = apr_pcalloc(result_pool, sizeof(*new_version));

  /* Shallow copy all members. */
  *new_version = *version;

  if (version->repos_url)
    new_version->repos_url = apr_pstrdup(result_pool, version->repos_url);

  if (version->path_in_repos)
    new_version->path_in_repos = apr_pstrdup(result_pool,
                                             version->path_in_repos);

  if (version->repos_uuid)
    new_version->repos_uuid = apr_pstrdup(result_pool, version->repos_uuid);

  return new_version;
}