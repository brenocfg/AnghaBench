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
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SERF_BUCKET_SIMPLE_STRING (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend_str (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__unparse_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_txn_post_body(serf_bucket_t **body_bkt,
                     void *baton,
                     serf_bucket_alloc_t *alloc,
                     apr_pool_t *pool /* request pool */,
                     apr_pool_t *scratch_pool)
{
  apr_hash_t *revprops = baton;
  svn_skel_t *request_skel;
  svn_stringbuf_t *skel_str;

  request_skel = svn_skel__make_empty_list(pool);
  if (revprops)
    {
      svn_skel_t *proplist_skel;

      SVN_ERR(svn_skel__unparse_proplist(&proplist_skel, revprops, pool));
      svn_skel__prepend(proplist_skel, request_skel);
      svn_skel__prepend_str("create-txn-with-props", request_skel, pool);
      skel_str = svn_skel__unparse(request_skel, pool);
      *body_bkt = SERF_BUCKET_SIMPLE_STRING(skel_str->data, alloc);
    }
  else
    {
      *body_bkt = SERF_BUCKET_SIMPLE_STRING("( create-txn )", alloc);
    }

  return SVN_NO_ERROR;
}