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
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_UTF_UTON_XLATE_HANDLE ; 
 int /*<<< orphan*/  check_cstring_utf8 (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert_cstring (char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_uton_xlate_handle_node (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_xlate_handle_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_utf_cstring_from_utf8(const char **dest,
                          const char *src,
                          apr_pool_t *pool)
{
  xlate_handle_node_t *node;
  svn_error_t *err;

  SVN_ERR(check_cstring_utf8(src, pool));

  SVN_ERR(get_uton_xlate_handle_node(&node, pool));
  err = convert_cstring(dest, src, node, pool);
  err = svn_error_compose_create(
          err,
          put_xlate_handle_node(node, SVN_UTF_UTON_XLATE_HANDLE, pool));

  return err;
}