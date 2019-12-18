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
typedef  int /*<<< orphan*/  xlate_handle_node_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_APR_LOCALE_CHARSET ; 
 int /*<<< orphan*/  SVN_APR_UTF8_CHARSET ; 
 int /*<<< orphan*/  SVN_UTF_UTON_XLATE_HANDLE ; 
 scalar_t__ assume_native_charset_is_utf8 ; 
 int /*<<< orphan*/ * get_xlate_handle_node (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_uton_xlate_handle_node(xlate_handle_node_t **ret, apr_pool_t *pool)
{
  return get_xlate_handle_node(ret,
                               assume_native_charset_is_utf8
                                 ? SVN_APR_UTF8_CHARSET
                                 : SVN_APR_LOCALE_CHARSET,
                               SVN_APR_UTF8_CHARSET,
                               SVN_UTF_UTON_XLATE_HANDLE, pool);
}