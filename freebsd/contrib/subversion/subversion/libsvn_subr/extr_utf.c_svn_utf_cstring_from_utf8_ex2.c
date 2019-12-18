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
 int /*<<< orphan*/  SVN_APR_UTF8_CHARSET ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_cstring_utf8 (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert_cstring (char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_xlate_handle_node (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* get_xlate_key (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_xlate_handle_node (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_utf_cstring_from_utf8_ex2(const char **dest,
                              const char *src,
                              const char *topage,
                              apr_pool_t *pool)
{
  xlate_handle_node_t *node;
  svn_error_t *err;
  const char *convset_key = get_xlate_key(topage, SVN_APR_UTF8_CHARSET,
                                          pool);

  SVN_ERR(check_cstring_utf8(src, pool));

  SVN_ERR(get_xlate_handle_node(&node, topage, SVN_APR_UTF8_CHARSET,
                                convset_key, pool));
  err = convert_cstring(dest, src, node, pool);
  err = svn_error_compose_create(
          err,
          put_xlate_handle_node(node, convset_key, pool));

  return err;
}