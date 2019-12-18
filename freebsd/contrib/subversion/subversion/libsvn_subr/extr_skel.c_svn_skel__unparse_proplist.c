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
struct TYPE_2__ {void const* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  is_valid_proplist_skel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skel_err (char*) ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__mem_atom (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_skel__unparse_proplist(svn_skel_t **skel_p,
                           const apr_hash_t *proplist,
                           apr_pool_t *pool)
{
  svn_skel_t *skel = svn_skel__make_empty_list(pool);
  apr_hash_index_t *hi;

  /* Create the skel. */
  if (proplist)
    {
      /* Loop over hash entries */
      for (hi = apr_hash_first(pool, (apr_hash_t *)proplist); hi;
           hi = apr_hash_next(hi))
        {
          const void *key;
          void *val;
          apr_ssize_t klen;
          svn_string_t *value;

          apr_hash_this(hi, &key, &klen, &val);
          value = val;

          /* VALUE */
          svn_skel__prepend(svn_skel__mem_atom(value->data, value->len, pool),
                            skel);

          /* NAME */
          svn_skel__prepend(svn_skel__mem_atom(key, klen, pool), skel);
        }
    }

  /* Validate and return the skel. */
  if (! is_valid_proplist_skel(skel))
    return skel_err("proplist");
  *skel_p = skel;
  return SVN_NO_ERROR;
}