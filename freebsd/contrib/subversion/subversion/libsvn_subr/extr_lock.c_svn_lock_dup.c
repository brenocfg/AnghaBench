#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* comment; void* owner; void* token; void* path; } ;
typedef  TYPE_1__ svn_lock_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,void*) ; 

svn_lock_t *
svn_lock_dup(const svn_lock_t *lock, apr_pool_t *pool)
{
  svn_lock_t *new_l;

  if (lock == NULL)
    return NULL;

  new_l = apr_palloc(pool, sizeof(*new_l));
  *new_l = *lock;

  new_l->path = apr_pstrdup(pool, new_l->path);
  new_l->token = apr_pstrdup(pool, new_l->token);
  new_l->owner = apr_pstrdup(pool, new_l->owner);
  new_l->comment = apr_pstrdup(pool, new_l->comment);

  return new_l;
}