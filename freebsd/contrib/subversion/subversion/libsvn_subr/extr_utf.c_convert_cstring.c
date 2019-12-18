#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ handle; } ;
typedef  TYPE_1__ xlate_handle_node_t ;
struct TYPE_7__ {char* data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_non_ascii (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  convert_to_stringbuf (TYPE_1__*,char const*,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static svn_error_t *
convert_cstring(const char **dest,
                const char *src,
                xlate_handle_node_t *node,
                apr_pool_t *pool)
{
  if (node->handle)
    {
      svn_stringbuf_t *destbuf;
      SVN_ERR(convert_to_stringbuf(node, src, strlen(src),
                                   &destbuf, pool));
      *dest = destbuf->data;
    }
  else
    {
      apr_size_t len = strlen(src);
      SVN_ERR(check_non_ascii(src, len, pool));
      *dest = apr_pstrmemdup(pool, src, len);
    }
  return SVN_NO_ERROR;
}