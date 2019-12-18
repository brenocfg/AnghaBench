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
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
struct TYPE_2__ {int nelts; int /*<<< orphan*/  elts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* apr_pmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

svn_error_t *
svn_fs_fs__serialize_manifest(void **data,
                              apr_size_t *data_len,
                              void *in,
                              apr_pool_t *pool)
{
  apr_array_header_t *manifest = in;

  *data_len = sizeof(apr_off_t) *manifest->nelts;
  *data = apr_pmemdup(pool, manifest->elts, *data_len);

  return SVN_NO_ERROR;
}