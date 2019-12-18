#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ xlate_handle_node_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_pool_get (int /*<<< orphan*/ ) ; 
 TYPE_1__** apr_palloc (int /*<<< orphan*/ ,int) ; 
 char* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__** svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,TYPE_1__**) ; 
 int /*<<< orphan*/  xlate_handle_hash ; 

__attribute__((used)) static svn_error_t *
put_xlate_handle_node_internal(xlate_handle_node_t *node,
                               const char *userdata_key)
{
  xlate_handle_node_t **node_p = svn_hash_gets(xlate_handle_hash, userdata_key);
  if (node_p == NULL)
    {
      userdata_key = apr_pstrdup(apr_hash_pool_get(xlate_handle_hash),
                                  userdata_key);
      node_p = apr_palloc(apr_hash_pool_get(xlate_handle_hash),
                          sizeof(*node_p));
      *node_p = NULL;
      svn_hash_sets(xlate_handle_hash, userdata_key, node_p);
    }
  node->next = *node_p;
  *node_p = node;

  return SVN_NO_ERROR;
}