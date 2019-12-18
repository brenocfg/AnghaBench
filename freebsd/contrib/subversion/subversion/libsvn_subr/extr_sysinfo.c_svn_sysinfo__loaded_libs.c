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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* macos_shared_libs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* win32_shared_libs (int /*<<< orphan*/ *) ; 

const apr_array_header_t *
svn_sysinfo__loaded_libs(apr_pool_t *pool)
{
#ifdef WIN32
  return win32_shared_libs(pool);
#elif defined(SVN_HAVE_MACHO_ITERATE)
  return macos_shared_libs(pool);
#else
  return NULL;
#endif
}