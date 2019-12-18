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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_stream_open_readonly (int /*<<< orphan*/ **,char const* const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_delta_base(svn_stream_t **stream, void *baton,
                apr_pool_t *result_pool, apr_pool_t *scratch_pool)
{
  const char *const delta_base = baton;
  return svn_stream_open_readonly(stream, delta_base,
                                  result_pool, scratch_pool);
}