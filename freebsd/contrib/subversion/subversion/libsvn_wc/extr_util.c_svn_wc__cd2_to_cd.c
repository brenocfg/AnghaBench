#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int kind; int /*<<< orphan*/ * access; int /*<<< orphan*/  operation; void* merged_file; void* my_file; void* their_file; void* base_file; void* mime_type; int /*<<< orphan*/  is_binary; void* property_name; void* src_right_version; void* src_left_version; int /*<<< orphan*/  reason; int /*<<< orphan*/  action; int /*<<< orphan*/  node_kind; void* path; } ;
typedef  TYPE_1__ svn_wc_conflict_description_t ;
struct TYPE_7__ {int kind; int /*<<< orphan*/  operation; int /*<<< orphan*/  merged_file; int /*<<< orphan*/  my_abspath; int /*<<< orphan*/  their_abspath; int /*<<< orphan*/  base_abspath; int /*<<< orphan*/  mime_type; int /*<<< orphan*/  is_binary; int /*<<< orphan*/  property_name; scalar_t__ src_right_version; scalar_t__ src_left_version; int /*<<< orphan*/  reason; int /*<<< orphan*/  action; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  local_abspath; } ;
typedef  TYPE_2__ svn_wc_conflict_description2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  svn_wc_conflict_kind_property 130 
#define  svn_wc_conflict_kind_text 129 
#define  svn_wc_conflict_kind_tree 128 
 void* svn_wc_conflict_version_dup (scalar_t__,int /*<<< orphan*/ *) ; 

svn_wc_conflict_description_t *
svn_wc__cd2_to_cd(const svn_wc_conflict_description2_t *conflict,
                  apr_pool_t *result_pool)
{
  svn_wc_conflict_description_t *new_conflict;

  if (conflict == NULL)
    return NULL;

  new_conflict = apr_pcalloc(result_pool, sizeof(*new_conflict));

  new_conflict->path = apr_pstrdup(result_pool, conflict->local_abspath);
  new_conflict->node_kind = conflict->node_kind;
  new_conflict->kind = conflict->kind;
  new_conflict->action = conflict->action;
  new_conflict->reason = conflict->reason;
  if (conflict->src_left_version)
    new_conflict->src_left_version =
          svn_wc_conflict_version_dup(conflict->src_left_version, result_pool);
  if (conflict->src_right_version)
    new_conflict->src_right_version =
          svn_wc_conflict_version_dup(conflict->src_right_version, result_pool);

  switch (conflict->kind)
    {

      case svn_wc_conflict_kind_property:
        new_conflict->property_name = apr_pstrdup(result_pool,
                                                  conflict->property_name);
        /* Falling through. */

      case svn_wc_conflict_kind_text:
        new_conflict->is_binary = conflict->is_binary;
        if (conflict->mime_type)
          new_conflict->mime_type = apr_pstrdup(result_pool,
                                                conflict->mime_type);
        if (conflict->base_abspath)
          new_conflict->base_file = apr_pstrdup(result_pool,
                                                conflict->base_abspath);
        if (conflict->their_abspath)
          new_conflict->their_file = apr_pstrdup(result_pool,
                                                 conflict->their_abspath);
        if (conflict->my_abspath)
          new_conflict->my_file = apr_pstrdup(result_pool,
                                              conflict->my_abspath);
        if (conflict->merged_file)
          new_conflict->merged_file = apr_pstrdup(result_pool,
                                                  conflict->merged_file);
        break;

      case svn_wc_conflict_kind_tree:
        new_conflict->operation = conflict->operation;
        break;
    }

  /* A NULL access baton is allowable by the API. */
  new_conflict->access = NULL;

  return new_conflict;
}