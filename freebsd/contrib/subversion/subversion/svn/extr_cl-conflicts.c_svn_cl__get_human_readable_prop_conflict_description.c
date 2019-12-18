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
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* _ (char*) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  map_conflict_action_xml ; 
 int /*<<< orphan*/  map_conflict_reason_xml ; 
 int /*<<< orphan*/  operation_str (int /*<<< orphan*/ ) ; 
 int svn_client_conflict_get_incoming_change (int /*<<< orphan*/ *) ; 
 int svn_client_conflict_get_local_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_operation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_token__to_word (int /*<<< orphan*/ ,int) ; 
#define  svn_wc_conflict_action_add 134 
#define  svn_wc_conflict_action_delete 133 
#define  svn_wc_conflict_action_edit 132 
#define  svn_wc_conflict_reason_added 131 
#define  svn_wc_conflict_reason_deleted 130 
#define  svn_wc_conflict_reason_edited 129 
#define  svn_wc_conflict_reason_obstructed 128 

svn_error_t *
svn_cl__get_human_readable_prop_conflict_description(
  const char **desc,
  svn_client_conflict_t *conflict,
  apr_pool_t *pool)
{
  const char *reason_str, *action_str;

  /* We provide separately translatable strings for the values that we
   * know about, and a fall-back in case any other values occur. */
  switch (svn_client_conflict_get_local_change(conflict))
    {
      case svn_wc_conflict_reason_edited:
        reason_str = _("local edit");
        break;
      case svn_wc_conflict_reason_added:
        reason_str = _("local add");
        break;
      case svn_wc_conflict_reason_deleted:
        reason_str = _("local delete");
        break;
      case svn_wc_conflict_reason_obstructed:
        reason_str = _("local obstruction");
        break;
      default:
        reason_str = apr_psprintf(
                       pool, _("local %s"),
                       svn_token__to_word(
                         map_conflict_reason_xml,
                         svn_client_conflict_get_local_change(conflict)));
        break;
    }
  switch (svn_client_conflict_get_incoming_change(conflict))
    {
      case svn_wc_conflict_action_edit:
        action_str = _("incoming edit");
        break;
      case svn_wc_conflict_action_add:
        action_str = _("incoming add");
        break;
      case svn_wc_conflict_action_delete:
        action_str = _("incoming delete");
        break;
      default:
        action_str = apr_psprintf(
                       pool, _("incoming %s"),
                       svn_token__to_word(
                         map_conflict_action_xml,
                         svn_client_conflict_get_incoming_change(conflict)));
        break;
    }
  SVN_ERR_ASSERT(reason_str && action_str);
  *desc = apr_psprintf(pool, _("%s, %s %s"),
                       reason_str, action_str,
                       operation_str(
                         svn_client_conflict_get_operation(conflict)));
  return SVN_NO_ERROR;
}