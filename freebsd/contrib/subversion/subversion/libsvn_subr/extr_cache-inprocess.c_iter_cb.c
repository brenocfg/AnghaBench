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
typedef  int /*<<< orphan*/  svn_error_t ;
struct cache_iter_baton {int /*<<< orphan*/  user_baton; int /*<<< orphan*/ * (* user_cb ) (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct cache_entry {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
iter_cb(void *baton,
        const void *key,
        apr_ssize_t klen,
        void *val,
        apr_pool_t *pool)
{
  struct cache_iter_baton *b = baton;
  struct cache_entry *entry = val;
  return (b->user_cb)(b->user_baton, key, klen, entry->value, pool);
}