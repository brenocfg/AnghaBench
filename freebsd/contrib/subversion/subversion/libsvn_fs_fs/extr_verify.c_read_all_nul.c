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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 scalar_t__ STREAM_THRESHOLD ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  expect_buffer_nul (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_all_nul(apr_file_t *file,
             apr_off_t size,
             apr_pool_t *pool)
{
  for (; size >= STREAM_THRESHOLD; size -= STREAM_THRESHOLD)
    SVN_ERR(expect_buffer_nul(file, STREAM_THRESHOLD, pool));

  if (size)
    SVN_ERR(expect_buffer_nul(file, size, pool));

  return SVN_NO_ERROR;
}