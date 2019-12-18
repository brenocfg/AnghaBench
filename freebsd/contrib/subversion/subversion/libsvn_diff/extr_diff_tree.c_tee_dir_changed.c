#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
struct tee_node_baton_t {int /*<<< orphan*/  baton2; int /*<<< orphan*/  baton1; } ;
struct tee_baton_t {TYPE_1__* p2; TYPE_2__* p1; } ;
struct svn_diff_tree_processor_t {struct tee_baton_t* baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* dir_changed ) (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* dir_changed ) (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
tee_dir_changed(const char *relpath,
                    const svn_diff_source_t *left_source,
                    const svn_diff_source_t *right_source,
                    /*const*/ apr_hash_t *left_props,
                    /*const*/ apr_hash_t *right_props,
                    const apr_array_header_t *prop_changes,
                    void *dir_baton,
                    const struct svn_diff_tree_processor_t *processor,
                    apr_pool_t *scratch_pool)
{
  struct tee_baton_t *tb = processor->baton;
  struct tee_node_baton_t *db = dir_baton;

  SVN_ERR(tb->p1->dir_changed(relpath,
                              left_source,
                              right_source,
                              left_props,
                              right_props,
                              prop_changes,
                              db->baton1,
                              tb->p1,
                              scratch_pool));

  SVN_ERR(tb->p2->dir_changed(relpath,
                              left_source,
                              right_source,
                              left_props,
                              right_props,
                              prop_changes,
                              db->baton2,
                              tb->p2,
                              scratch_pool));
  return SVN_NO_ERROR;
}