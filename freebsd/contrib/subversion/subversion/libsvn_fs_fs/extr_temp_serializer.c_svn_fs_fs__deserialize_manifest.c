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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
struct TYPE_3__ {int nelts; int nalloc; char* elts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_array_make (int /*<<< orphan*/ *,int,int) ; 

svn_error_t *
svn_fs_fs__deserialize_manifest(void **out,
                                void *data,
                                apr_size_t data_len,
                                apr_pool_t *pool)
{
  apr_array_header_t *manifest = apr_array_make(pool, 1, sizeof(apr_off_t));

  manifest->nelts = (int) (data_len / sizeof(apr_off_t));
  manifest->nalloc = (int) (data_len / sizeof(apr_off_t));
  manifest->elts = (char*)data;

  *out = manifest;

  return SVN_NO_ERROR;
}