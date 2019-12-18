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
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_config_dup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash__make (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_config_copy_config(apr_hash_t **cfg_hash,
                       apr_hash_t *src_hash,
                       apr_pool_t *pool)
{
  apr_hash_index_t *cidx;

  *cfg_hash = svn_hash__make(pool);
  for (cidx = apr_hash_first(pool, src_hash);
       cidx != NULL;
       cidx = apr_hash_next(cidx))
  {
    const void *ckey;
    void *cval;
    apr_ssize_t ckeyLength;
    svn_config_t * srcconfig;
    svn_config_t * destconfig;

    apr_hash_this(cidx, &ckey, &ckeyLength, &cval);
    srcconfig = cval;

    SVN_ERR(svn_config_dup(&destconfig, srcconfig, pool));

    apr_hash_set(*cfg_hash,
                 apr_pstrdup(pool, (const char*)ckey),
                 ckeyLength, destconfig);
  }

  return SVN_NO_ERROR;
}