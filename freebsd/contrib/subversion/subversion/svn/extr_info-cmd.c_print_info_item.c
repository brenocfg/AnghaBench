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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {char* URL; char* repos_root_URL; char* repos_UUID; char* last_changed_author; TYPE_1__* wc_info; int /*<<< orphan*/  last_changed_date; int /*<<< orphan*/  last_changed_rev; int /*<<< orphan*/  rev; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ svn_client_info2_t ;
struct TYPE_8__ {int print_what; scalar_t__ start_new_line; int /*<<< orphan*/  path_prefix; int /*<<< orphan*/  target_is_path; int /*<<< orphan*/  multiple_targets; } ;
typedef  TYPE_3__ print_info_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {char* wcroot_abspath; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
#define  info_item_kind 137 
#define  info_item_last_changed_author 136 
#define  info_item_last_changed_date 135 
#define  info_item_last_changed_rev 134 
#define  info_item_relative_url 133 
#define  info_item_repos_root_url 132 
#define  info_item_repos_uuid 131 
#define  info_item_revision 130 
#define  info_item_url 129 
#define  info_item_wc_root 128 
 int /*<<< orphan*/  print_info_item_revision (int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_info_item_string (char*,char const* const,int /*<<< orphan*/ *) ; 
 char* relative_url (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 char* svn_cl__local_style_skip_ancestor (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cmdline_fputs (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_node_kind_to_word (int /*<<< orphan*/ ) ; 
 char* svn_time_to_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
print_info_item(void *baton,
                  const char *target,
                  const svn_client_info2_t *info,
                  apr_pool_t *pool)
{
  print_info_baton_t *const receiver_baton = baton;
  const char *const target_path =
    (!receiver_baton->multiple_targets ? NULL
     : (!receiver_baton->target_is_path ? info->URL
        : svn_cl__local_style_skip_ancestor(
            receiver_baton->path_prefix, target, pool)));

  if (receiver_baton->start_new_line)
    SVN_ERR(svn_cmdline_fputs("\n", stdout, pool));

  switch (receiver_baton->print_what)
    {
    case info_item_kind:
      SVN_ERR(print_info_item_string(svn_node_kind_to_word(info->kind),
                                     target_path, pool));
      break;

    case info_item_url:
      SVN_ERR(print_info_item_string(info->URL, target_path, pool));
      break;

    case info_item_relative_url:
      SVN_ERR(print_info_item_string(relative_url(info, pool),
                                     target_path, pool));
      break;

    case info_item_repos_root_url:
      SVN_ERR(print_info_item_string(info->repos_root_URL, target_path, pool));
      break;

    case info_item_repos_uuid:
      SVN_ERR(print_info_item_string(info->repos_UUID, target_path, pool));
      break;

    case info_item_revision:
      SVN_ERR(print_info_item_revision(info->rev, target_path, pool));
      break;

    case info_item_last_changed_rev:
      SVN_ERR(print_info_item_revision(info->last_changed_rev,
                                       target_path, pool));
      break;

    case info_item_last_changed_date:
      SVN_ERR(print_info_item_string(
                  (!info->last_changed_date ? NULL
                   : svn_time_to_cstring(info->last_changed_date, pool)),
                  target_path, pool));
      break;

    case info_item_last_changed_author:
      SVN_ERR(print_info_item_string(info->last_changed_author,
                                     target_path, pool));
      break;

    case info_item_wc_root:
      SVN_ERR(print_info_item_string(
                  (info->wc_info && info->wc_info->wcroot_abspath
                   ? info->wc_info->wcroot_abspath : NULL),
                  target_path, pool));
      break;

    default:
      SVN_ERR_MALFUNCTION();
    }

  receiver_baton->start_new_line = TRUE;
  return SVN_NO_ERROR;
}