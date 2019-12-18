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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_datasource_e ;
struct fns_wrapper_baton {int /*<<< orphan*/  old_baton; TYPE_1__* vtable; } ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* datasource_get_next_token ) (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
datasource_get_next_token(apr_uint32_t *hash,
                          void **token,
                          void *baton,
                          svn_diff_datasource_e datasource)
{
  struct fns_wrapper_baton *fwb = baton;
  return fwb->vtable->datasource_get_next_token(hash, token, fwb->old_baton,
                                                datasource);
}