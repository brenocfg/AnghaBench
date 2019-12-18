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
typedef  int /*<<< orphan*/  svn_atomic_t ;
typedef  scalar_t__ apr_status_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_threadkey_private_set (void*,scalar_t__) ; 
 char const* error_file ; 
 scalar_t__ error_file_key ; 
 long error_line ; 
 scalar_t__ error_line_key ; 
 int /*<<< orphan*/  locate_init_once ; 
 int /*<<< orphan*/  svn_atomic__init_once_no_error (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
svn_error__locate(const char *file, long line)
{
#ifdef SVN_DEBUG
#  if APR_HAS_THREADS
  static volatile svn_atomic_t init_status = 0;
  svn_atomic__init_once_no_error(&init_status, locate_init_once, NULL);

  if (error_file_key && error_line_key)
    {
      apr_status_t status;
      status = apr_threadkey_private_set((char*)file, error_file_key);
      if (status == APR_SUCCESS)
        status = apr_threadkey_private_set((void*)line, error_line_key);
      if (status == APR_SUCCESS)
        return;
    }
#  endif  /* APR_HAS_THREADS */

  error_file = file;
  error_line = line;
#endif /* SVN_DEBUG */
}