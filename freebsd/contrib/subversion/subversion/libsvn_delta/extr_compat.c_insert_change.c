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
struct change_node {void* deleting; void* changing; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 struct change_node* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 struct change_node* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct change_node*) ; 

__attribute__((used)) static struct change_node *
insert_change(const char *relpath,
              apr_hash_t *changes)
{
  apr_pool_t *result_pool;
  struct change_node *change;

  change = svn_hash_gets(changes, relpath);
  if (change != NULL)
    return change;

  result_pool = apr_hash_pool_get(changes);

  /* Return an empty change. Callers will tweak as needed.  */
  change = apr_pcalloc(result_pool, sizeof(*change));
  change->changing = SVN_INVALID_REVNUM;
  change->deleting = SVN_INVALID_REVNUM;

  svn_hash_sets(changes, apr_pstrdup(result_pool, relpath), change);

  return change;
}