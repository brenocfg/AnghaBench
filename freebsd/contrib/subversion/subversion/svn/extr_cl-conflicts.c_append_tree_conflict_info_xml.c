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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_conflict_version_xml (int /*<<< orphan*/ **,char*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_conflict_action_xml ; 
 int /*<<< orphan*/  map_conflict_reason_xml ; 
 char const* svn_cl__node_kind_str_xml (int /*<<< orphan*/ ) ; 
 char const* svn_cl__operation_str_xml (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_old_repos_location (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_local_abspath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_local_change (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_operation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_get_repos_info (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_conflict_tree_get_victim_node_kind (int /*<<< orphan*/ *) ; 
 char const* svn_dirent_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char*,char const*) ; 
 char* svn_token__to_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_xml_make_close_tag (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_xml_make_open_tag_hash (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_normal ; 

__attribute__((used)) static svn_error_t *
append_tree_conflict_info_xml(svn_stringbuf_t *str,
                              svn_client_conflict_t *conflict,
                              apr_pool_t *pool)
{
  apr_hash_t *att_hash = apr_hash_make(pool);
  const char *tmp;
  const char *repos_root_url;
  const char *repos_relpath;
  svn_revnum_t peg_rev;
  svn_node_kind_t node_kind;

  svn_hash_sets(att_hash, "victim",
                svn_dirent_basename(
                  svn_client_conflict_get_local_abspath(conflict), pool));

  svn_hash_sets(att_hash, "kind",
                svn_cl__node_kind_str_xml(
                  svn_client_conflict_tree_get_victim_node_kind(conflict)));

  svn_hash_sets(att_hash, "operation",
                svn_cl__operation_str_xml(
                  svn_client_conflict_get_operation(conflict), pool));

  tmp = svn_token__to_word(map_conflict_action_xml,
                           svn_client_conflict_get_incoming_change(conflict));
  svn_hash_sets(att_hash, "action", tmp);

  tmp = svn_token__to_word(map_conflict_reason_xml,
                           svn_client_conflict_get_local_change(conflict));
  svn_hash_sets(att_hash, "reason", tmp);

  /* Open the tree-conflict tag. */
  svn_xml_make_open_tag_hash(&str, pool, svn_xml_normal,
                             "tree-conflict", att_hash);

  /* Add child tags for OLDER_VERSION and THEIR_VERSION. */

  SVN_ERR(svn_client_conflict_get_repos_info(&repos_root_url, NULL, conflict,
                                             pool, pool));
  SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(&repos_relpath,
                                                              &peg_rev,
                                                              &node_kind,
                                                              conflict,
                                                              pool,
                                                              pool));
  if (repos_root_url && repos_relpath)
    SVN_ERR(add_conflict_version_xml(&str, "source-left",
                                     repos_root_url, repos_relpath, peg_rev,
                                     node_kind, pool));

  SVN_ERR(svn_client_conflict_get_incoming_old_repos_location(&repos_relpath,
                                                              &peg_rev,
                                                              &node_kind,
                                                              conflict,
                                                              pool,
                                                              pool));
  if (repos_root_url && repos_relpath)
    SVN_ERR(add_conflict_version_xml(&str,
                                     "source-right",
                                     repos_root_url, repos_relpath, peg_rev,
                                     node_kind, pool));

  svn_xml_make_close_tag(&str, pool, "tree-conflict");

  return SVN_NO_ERROR;
}