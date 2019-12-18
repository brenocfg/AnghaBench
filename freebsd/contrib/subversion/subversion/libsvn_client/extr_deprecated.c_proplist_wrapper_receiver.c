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
struct proplist_receiver_wrapper_baton {int /*<<< orphan*/  baton; int /*<<< orphan*/ * (* receiver ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
proplist_wrapper_receiver(void *baton,
                          const char *path,
                          apr_hash_t *prop_hash,
                          apr_array_header_t *inherited_props,
                          apr_pool_t *pool)
{
  struct proplist_receiver_wrapper_baton *plrwb = baton;

  if (plrwb->receiver)
    return plrwb->receiver(plrwb->baton, path, prop_hash, pool);

  return SVN_NO_ERROR;
}