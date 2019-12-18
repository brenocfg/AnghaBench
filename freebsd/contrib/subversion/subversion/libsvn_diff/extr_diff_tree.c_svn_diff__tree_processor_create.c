#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  node_absent; int /*<<< orphan*/  file_closed; int /*<<< orphan*/  file_changed; int /*<<< orphan*/  file_deleted; int /*<<< orphan*/  file_added; int /*<<< orphan*/  file_opened; int /*<<< orphan*/  dir_closed; int /*<<< orphan*/  dir_changed; int /*<<< orphan*/  dir_deleted; int /*<<< orphan*/  dir_added; int /*<<< orphan*/  dir_opened; void* baton; } ;
struct TYPE_5__ {TYPE_2__ tp; } ;
typedef  TYPE_1__ tree_processor_t ;
typedef  TYPE_2__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  default_dir_added ; 
 int /*<<< orphan*/  default_dir_changed ; 
 int /*<<< orphan*/  default_dir_closed ; 
 int /*<<< orphan*/  default_dir_deleted ; 
 int /*<<< orphan*/  default_dir_opened ; 
 int /*<<< orphan*/  default_file_added ; 
 int /*<<< orphan*/  default_file_changed ; 
 int /*<<< orphan*/  default_file_closed ; 
 int /*<<< orphan*/  default_file_deleted ; 
 int /*<<< orphan*/  default_file_opened ; 
 int /*<<< orphan*/  default_node_absent ; 

svn_diff_tree_processor_t *
svn_diff__tree_processor_create(void *baton,
                                apr_pool_t *result_pool)
{
  tree_processor_t *wrapper;
  wrapper = apr_pcalloc(result_pool, sizeof(*wrapper));

  wrapper->tp.baton        = baton;

  wrapper->tp.dir_opened   = default_dir_opened;
  wrapper->tp.dir_added    = default_dir_added;
  wrapper->tp.dir_deleted  = default_dir_deleted;
  wrapper->tp.dir_changed  = default_dir_changed;
  wrapper->tp.dir_closed   = default_dir_closed;

  wrapper->tp.file_opened   = default_file_opened;
  wrapper->tp.file_added    = default_file_added;
  wrapper->tp.file_deleted  = default_file_deleted;
  wrapper->tp.file_changed  = default_file_changed;
  wrapper->tp.file_closed   = default_file_closed;

  wrapper->tp.node_absent   = default_node_absent;


  return &wrapper->tp;
}