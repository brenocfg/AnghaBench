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
struct TYPE_2__ {int /*<<< orphan*/  file_size; } ;
typedef  TYPE_1__ p2l_header_t ;
typedef  int /*<<< orphan*/  max_offset ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* apr_pmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_error_t *
p2l_get_max_offset_func(void **out,
                        const void *data,
                        apr_size_t data_len,
                        void *baton,
                        apr_pool_t *result_pool)
{
  const p2l_header_t *header = data;
  apr_off_t max_offset = header->file_size;
  *out = apr_pmemdup(result_pool, &max_offset, sizeof(max_offset));

  return SVN_NO_ERROR;
}