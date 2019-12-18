#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int current_line; int /*<<< orphan*/  write_baton; int /*<<< orphan*/  write; TYPE_2__* read_baton; int /*<<< orphan*/  seek; int /*<<< orphan*/  tell; int /*<<< orphan*/  readline; int /*<<< orphan*/  existed; int /*<<< orphan*/  keywords; void* hunks; void* lines; int /*<<< orphan*/  eol_style; } ;
typedef  TYPE_1__ target_content_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_operation_kind_t ;
struct TYPE_8__ {scalar_t__ offset; int /*<<< orphan*/  const* value; } ;
typedef  TYPE_2__ prop_read_baton_t ;
struct TYPE_9__ {int /*<<< orphan*/  patched_value; int /*<<< orphan*/  const* value; TYPE_1__* content; int /*<<< orphan*/  operation; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ prop_patch_target_t ;
struct TYPE_10__ {scalar_t__ db_kind; scalar_t__ deleted; } ;
typedef  TYPE_4__ patch_target_t ;
typedef  int /*<<< orphan*/  hunk_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  readline_prop ; 
 int /*<<< orphan*/  seek_prop ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_subst_eol_style_none ; 
 int /*<<< orphan*/  svn_wc_prop_get2 (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tell_prop ; 
 int /*<<< orphan*/  write_prop ; 

__attribute__((used)) static svn_error_t *
init_prop_target(prop_patch_target_t **prop_target,
                 const patch_target_t *target,
                 const char *prop_name,
                 svn_diff_operation_kind_t operation,
                 svn_wc_context_t *wc_ctx,
                 const char *local_abspath,
                 apr_pool_t *result_pool, apr_pool_t *scratch_pool)
{
  prop_patch_target_t *new_prop_target;
  target_content_t *content;
  const svn_string_t *value;
  prop_read_baton_t *prop_read_baton;

  content = apr_pcalloc(result_pool, sizeof(*content));

  /* All other fields are FALSE or NULL due to apr_pcalloc(). */
  content->current_line = 1;
  content->eol_style = svn_subst_eol_style_none;
  content->lines = apr_array_make(result_pool, 0, sizeof(apr_off_t));
  content->hunks = apr_array_make(result_pool, 0, sizeof(hunk_info_t *));
  content->keywords = apr_hash_make(result_pool);

  new_prop_target = apr_pcalloc(result_pool, sizeof(*new_prop_target));
  new_prop_target->name = apr_pstrdup(result_pool, prop_name);
  new_prop_target->operation = operation;
  new_prop_target->content = content;

  if (!(target->deleted || target->db_kind == svn_node_none))
    SVN_ERR(svn_wc_prop_get2(&value, wc_ctx, local_abspath, prop_name,
                             result_pool, scratch_pool));
  else
    value = NULL;

  content->existed = (value != NULL);
  new_prop_target->value = value;
  new_prop_target->patched_value = svn_stringbuf_create_empty(result_pool);


  /* Wire up the read and write callbacks. */
  prop_read_baton = apr_pcalloc(result_pool, sizeof(*prop_read_baton));
  prop_read_baton->value = value;
  prop_read_baton->offset = 0;
  content->readline = readline_prop;
  content->tell = tell_prop;
  content->seek = seek_prop;
  content->read_baton = prop_read_baton;
  content->write = write_prop;
  content->write_baton = new_prop_target->patched_value;

  *prop_target = new_prop_target;

  return SVN_NO_ERROR;
}