#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  offsets; } ;
typedef  TYPE_1__ p2l_header_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  p2l_page_info_copy (void*,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_temp_deserializer__ptr (TYPE_1__ const*,void const* const*) ; 

__attribute__((used)) static svn_error_t *
p2l_page_info_func(void **out,
                   const void *data,
                   apr_size_t data_len,
                   void *baton,
                   apr_pool_t *result_pool)
{
  /* all the pointers to cached data we need */
  const p2l_header_t *header = data;
  const apr_off_t *offsets
    = svn_temp_deserializer__ptr(header,
                                 (const void *const *)&header->offsets);

  /* copy data from cache to BATON */
  p2l_page_info_copy(baton, header, offsets);
  return SVN_NO_ERROR;
}