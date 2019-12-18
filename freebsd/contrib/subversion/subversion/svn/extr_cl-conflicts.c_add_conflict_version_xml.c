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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char const* apr_ltoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* svn_cl__node_kind_str_xml (scalar_t__) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ svn_node_unknown ; 
 int /*<<< orphan*/  svn_xml_make_open_tag_hash (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_xml_self_closing ; 

__attribute__((used)) static svn_error_t *
add_conflict_version_xml(svn_stringbuf_t **pstr,
                         const char *side,
                         const char *repos_root_url,
                         const char *repos_relpath,
                         svn_revnum_t peg_rev,
                         svn_node_kind_t node_kind,
                         apr_pool_t *pool)
{
  apr_hash_t *att_hash = apr_hash_make(pool);


  svn_hash_sets(att_hash, "side", side);

  if (repos_root_url)
    svn_hash_sets(att_hash, "repos-url", repos_root_url);

  if (repos_relpath)
    svn_hash_sets(att_hash, "path-in-repos", repos_relpath);

  if (SVN_IS_VALID_REVNUM(peg_rev))
    svn_hash_sets(att_hash, "revision", apr_ltoa(pool, peg_rev));

  if (node_kind != svn_node_unknown)
    svn_hash_sets(att_hash, "kind", svn_cl__node_kind_str_xml(node_kind));

  svn_xml_make_open_tag_hash(pstr, pool, svn_xml_self_closing,
                             "version", att_hash);
  return SVN_NO_ERROR;
}