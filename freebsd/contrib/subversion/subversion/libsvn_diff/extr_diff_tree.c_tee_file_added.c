#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {struct tee_baton_t* baton; } ;
typedef  TYPE_1__ svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
struct tee_node_baton_t {int /*<<< orphan*/  baton2; int /*<<< orphan*/  baton1; } ;
struct tee_baton_t {TYPE_3__* p2; TYPE_4__* p1; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* file_added ) (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* file_added ) (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
tee_file_added(const char *relpath,
               const svn_diff_source_t *copyfrom_source,
               const svn_diff_source_t *right_source,
               const char *copyfrom_file,
               const char *right_file,
               /*const*/ apr_hash_t *copyfrom_props,
               /*const*/ apr_hash_t *right_props,
               void *file_baton,
               const svn_diff_tree_processor_t *processor,
               apr_pool_t *scratch_pool)
{
  struct tee_baton_t *tb = processor->baton;
  struct tee_node_baton_t *fb = file_baton;

  SVN_ERR(tb->p1->file_added(relpath,
                             copyfrom_source,
                             right_source,
                             copyfrom_file,
                             right_file,
                             copyfrom_props,
                             right_props,
                             fb->baton1,
                             tb->p1,
                             scratch_pool));

  SVN_ERR(tb->p2->file_added(relpath,
                             copyfrom_source,
                             right_source,
                             copyfrom_file,
                             right_file,
                             copyfrom_props,
                             right_props,
                             fb->baton2,
                             tb->p2,
                             scratch_pool));
  return SVN_NO_ERROR;
}