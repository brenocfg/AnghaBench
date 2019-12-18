#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_version_t ;
typedef  int svn_wc_conflict_reason_t ;
struct TYPE_15__ {int action; int reason; } ;
typedef  TYPE_3__ svn_wc_conflict_description2_t ;
typedef  int svn_wc_conflict_action_t ;
struct TYPE_16__ {struct TYPE_16__ const* next; TYPE_2__* children; } ;
typedef  TYPE_4__ const svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_17__ {char* data; } ;
struct TYPE_14__ {TYPE_1__* next; } ;
struct TYPE_13__ {TYPE_4__ const* next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_conflict_skel (TYPE_4__ const*) ; 
 int /*<<< orphan*/  node_kind_map ; 
 int /*<<< orphan*/  read_enum_field (int*,int /*<<< orphan*/ ,TYPE_4__ const*) ; 
 int /*<<< orphan*/  read_node_version_info (int /*<<< orphan*/  const**,TYPE_4__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 TYPE_8__* svn_skel__unparse (TYPE_4__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_action_map ; 
 int /*<<< orphan*/  svn_wc__conflict_reason_map ; 
 int /*<<< orphan*/  svn_wc__operation_map ; 
 TYPE_3__* svn_wc_conflict_description_create_tree2 (char const*,scalar_t__,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__deserialize_conflict(const svn_wc_conflict_description2_t **conflict,
                             const svn_skel_t *skel,
                             const char *dir_path,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  const char *victim_basename;
  const char *victim_abspath;
  svn_node_kind_t node_kind;
  svn_wc_operation_t operation;
  svn_wc_conflict_action_t action;
  svn_wc_conflict_reason_t reason;
  const svn_wc_conflict_version_t *src_left_version;
  const svn_wc_conflict_version_t *src_right_version;
  int n;
  svn_wc_conflict_description2_t *new_conflict;

  if (!is_valid_conflict_skel(skel))
    return svn_error_createf(SVN_ERR_WC_CORRUPT, NULL,
                             _("Invalid conflict info '%s' in tree conflict "
                               "description"),
                             skel ? svn_skel__unparse(skel, scratch_pool)->data
                                  : "(null)");

  /* victim basename */
  victim_basename = apr_pstrmemdup(scratch_pool,
                                   skel->children->next->data,
                                   skel->children->next->len);
  if (victim_basename[0] == '\0')
    return svn_error_create(SVN_ERR_WC_CORRUPT, NULL,
                            _("Empty 'victim' field in tree conflict "
                              "description"));

  /* node_kind */
  SVN_ERR(read_enum_field(&n, node_kind_map, skel->children->next->next));
  node_kind = (svn_node_kind_t)n;
  if (node_kind != svn_node_file && node_kind != svn_node_dir)
    return svn_error_create(SVN_ERR_WC_CORRUPT, NULL,
             _("Invalid 'node_kind' field in tree conflict description"));

  /* operation */
  SVN_ERR(read_enum_field(&n, svn_wc__operation_map,
                          skel->children->next->next->next));
  operation = (svn_wc_operation_t)n;

  SVN_ERR(svn_dirent_get_absolute(&victim_abspath,
                    svn_dirent_join(dir_path, victim_basename, scratch_pool),
                    scratch_pool));

  /* action */
  SVN_ERR(read_enum_field(&n, svn_wc__conflict_action_map,
                          skel->children->next->next->next->next));
  action = n;

  /* reason */
  SVN_ERR(read_enum_field(&n, svn_wc__conflict_reason_map,
                          skel->children->next->next->next->next->next));
  reason = n;

  /* Let's just make it a bit easier on ourself here... */
  skel = skel->children->next->next->next->next->next->next;

  /* src_left_version */
  SVN_ERR(read_node_version_info(&src_left_version, skel,
                                 result_pool, scratch_pool));

  /* src_right_version */
  SVN_ERR(read_node_version_info(&src_right_version, skel->next,
                                 result_pool, scratch_pool));

  new_conflict = svn_wc_conflict_description_create_tree2(victim_abspath,
    node_kind, operation, src_left_version, src_right_version,
    result_pool);
  new_conflict->action = action;
  new_conflict->reason = reason;

  *conflict = new_conflict;

  return SVN_NO_ERROR;
}