#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_9__ {TYPE_2__* dag_node_cache; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_10__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ svn_fs_x__dag_cache_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
struct TYPE_11__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_3__ cache_entry_t ;
struct TYPE_13__ {TYPE_1__* fsap_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  change_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  auto_clear_dag_cache (TYPE_2__*) ; 
 TYPE_3__* cache_lookup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_path (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_x__dag_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_fs_x__dag_get_created_path (int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_fs_x__dag_get_fs (int /*<<< orphan*/ *) ; 
 TYPE_4__* svn_fs_x__dag_get_id (int /*<<< orphan*/ *) ; 

void
svn_fs_x__update_dag_cache(dag_node_t *node)
{
  svn_fs_x__data_t *ffd = svn_fs_x__dag_get_fs(node)->fsap_data;
  const char *path = svn_fs_x__dag_get_created_path(node);
  svn_fs_x__dag_cache_t *cache = ffd->dag_node_cache;

  cache_entry_t *bucket;
  svn_string_t normalized;

  auto_clear_dag_cache(cache);
  bucket = cache_lookup(cache, svn_fs_x__dag_get_id(node)->change_set,
                        normalize_path(&normalized, path));
  bucket->node = svn_fs_x__dag_dup(node, cache->pool);
}