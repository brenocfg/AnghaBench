#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  eol; } ;
typedef  TYPE_1__ svn_fs_fs__changes_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {scalar_t__ change_count; int /*<<< orphan*/  revision; } ;
typedef  TYPE_2__ revision_info_t ;
struct TYPE_12__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_3__ query_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {scalar_t__ nelts; } ;
typedef  TYPE_4__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__create_changes_context (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__get_changes (TYPE_4__**,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_phys_change_count(query_t *query,
                      revision_info_t *revision_info,
                      apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  svn_fs_fs__changes_context_t *context;

  /* Fetch the first block of data. */
  SVN_ERR(svn_fs_fs__create_changes_context(&context, query->fs,
                                            revision_info->revision,
                                            scratch_pool));

  revision_info->change_count = 0;
  while (!context->eol)
    {
      apr_array_header_t *changes;

      svn_pool_clear(iterpool);
      SVN_ERR(svn_fs_fs__get_changes(&changes, context, iterpool, iterpool));
      revision_info->change_count = changes->nelts;
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}