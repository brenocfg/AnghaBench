#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kind; void* copyfrom_rev; void* revision; } ;
typedef  TYPE_1__ svn_client_commit_item3_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* SVN_INVALID_REVNUM ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_node_unknown ; 

svn_client_commit_item3_t *
svn_client_commit_item3_create(apr_pool_t *pool)
{
  svn_client_commit_item3_t *item = apr_pcalloc(pool, sizeof(*item));

  item->revision = SVN_INVALID_REVNUM;
  item->copyfrom_rev = SVN_INVALID_REVNUM;
  item->kind = svn_node_unknown;

  return item;
}