#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; TYPE_1__* next; struct TYPE_6__* children; } ;
typedef  TYPE_2__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_proplist_skel (TYPE_2__ const*) ; 
 int /*<<< orphan*/ * skel_err (char*) ; 
 int /*<<< orphan*/ * svn_string_ncreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_skel__parse_proplist(apr_hash_t **proplist_p,
                         const svn_skel_t *skel,
                         apr_pool_t *pool /* result_pool */)
{
  apr_hash_t *proplist = NULL;
  svn_skel_t *elt;

  /* Validate the skel. */
  if (! is_valid_proplist_skel(skel))
    return skel_err("proplist");

  /* Create the returned structure */
  proplist = apr_hash_make(pool);
  for (elt = skel->children; elt; elt = elt->next->next)
    {
      svn_string_t *value = svn_string_ncreate(elt->next->data,
                                               elt->next->len, pool);
      apr_hash_set(proplist,
                   apr_pstrmemdup(pool, elt->data, elt->len),
                   elt->len,
                   value);
    }

  /* Return the structure. */
  *proplist_p = proplist;
  return SVN_NO_ERROR;
}