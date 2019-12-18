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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct fp_baton {int /*<<< orphan*/  cb_baton; int /*<<< orphan*/  (* provide_props_cb ) (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
fetch_props(apr_hash_t **props,
            void *baton,
            const char *repos_relpath,
            svn_revnum_t base_revision,
            apr_pool_t *result_pool,
            apr_pool_t *scratch_pool)
{
  struct fp_baton *fpb = baton;
  svn_revnum_t unused_revision;

  /* Ignored: BASE_REVISION.  */

  return svn_error_trace(fpb->provide_props_cb(props, &unused_revision,
                                               fpb->cb_baton,
                                               repos_relpath,
                                               result_pool, scratch_pool));
}