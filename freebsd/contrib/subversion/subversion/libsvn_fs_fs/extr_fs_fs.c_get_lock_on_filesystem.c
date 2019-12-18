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

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io__file_lock_autocreate (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_lock_on_filesystem(const char *lock_filename,
                       apr_pool_t *pool)
{
  return svn_error_trace(svn_io__file_lock_autocreate(lock_filename, pool));
}