#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ xlate_handle_node_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* SVN_UTF_NTOU_XLATE_HANDLE ; 
 char const* SVN_UTF_UTON_XLATE_HANDLE ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_userdata_set (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* atomic_swap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  put_xlate_handle_node_internal (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  xlat_ntou_static_handle ; 
 int /*<<< orphan*/  xlat_uton_static_handle ; 
 scalar_t__ xlate_handle_hash ; 
 int /*<<< orphan*/  xlate_handle_mutex ; 

__attribute__((used)) static svn_error_t *
put_xlate_handle_node(xlate_handle_node_t *node,
                      const char *userdata_key,
                      apr_pool_t *pool)
{
  assert(node->next == NULL);
  if (!userdata_key)
    return SVN_NO_ERROR;

  /* push previous global node to the hash */
  if (xlate_handle_hash)
    {
      /* 1st level: global, static items */
      if (userdata_key == SVN_UTF_NTOU_XLATE_HANDLE)
        node = atomic_swap(&xlat_ntou_static_handle, node);
      else if (userdata_key == SVN_UTF_UTON_XLATE_HANDLE)
        node = atomic_swap(&xlat_uton_static_handle, node);
      if (node == NULL)
        return SVN_NO_ERROR;

      SVN_MUTEX__WITH_LOCK(xlate_handle_mutex,
                           put_xlate_handle_node_internal(node,
                                                          userdata_key));
    }
  else
    {
      /* Store it in the per-pool cache. */
      apr_pool_userdata_set(node, userdata_key, apr_pool_cleanup_null, pool);
    }

  return SVN_NO_ERROR;
}