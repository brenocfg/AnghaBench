#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
struct TYPE_7__ {size_t last_non_empty; TYPE_3__* buckets; } ;
typedef  TYPE_2__ svn_fs_x__dag_cache_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_8__ {scalar_t__ path_len; int /*<<< orphan*/ * node; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ cache_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static dag_node_t *
cache_lookup_last_path(svn_fs_x__dag_cache_t *cache,
                       const svn_string_t *path)
{
  cache_entry_t *result = &cache->buckets[cache->last_non_empty];

  if (   result->node
      && (result->path_len == path->len)
      && !memcmp(result->path, path->data, path->len))
    {
      return result->node;
    }

  return NULL;
}