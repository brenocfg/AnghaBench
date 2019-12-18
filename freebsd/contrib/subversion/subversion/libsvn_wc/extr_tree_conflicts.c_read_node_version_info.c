#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_conflict_version_t ;
struct TYPE_12__ {TYPE_4__* children; } ;
typedef  TYPE_5__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {TYPE_3__* next; } ;
struct TYPE_10__ {TYPE_2__* next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__* next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_STR_TO_REV (char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_version_info_skel (TYPE_5__ const*) ; 
 int /*<<< orphan*/  node_kind_map ; 
 int /*<<< orphan*/  read_enum_field (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_uri_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_conflict_version_create2 (char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_node_version_info(const svn_wc_conflict_version_t **version_info,
                       const svn_skel_t *skel,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  int n;
  const char *repos_root;
  const char *repos_relpath;
  svn_revnum_t peg_rev;
  svn_node_kind_t kind;

  if (!is_valid_version_info_skel(skel))
    return svn_error_create(SVN_ERR_WC_CORRUPT, NULL,
                            _("Invalid version info in tree conflict "
                              "description"));

  repos_root = apr_pstrmemdup(scratch_pool,
                              skel->children->next->data,
                              skel->children->next->len);
  if (*repos_root == '\0')
    {
      *version_info = NULL;
      return SVN_NO_ERROR;
    }

  /* Apply the Subversion 1.7+ url canonicalization rules to a pre 1.7 url */
  repos_root = svn_uri_canonicalize(repos_root, result_pool);

  peg_rev = SVN_STR_TO_REV(apr_pstrmemdup(scratch_pool,
                                          skel->children->next->next->data,
                                          skel->children->next->next->len));

  repos_relpath = apr_pstrmemdup(result_pool,
                                 skel->children->next->next->next->data,
                                 skel->children->next->next->next->len);

  SVN_ERR(read_enum_field(&n, node_kind_map,
                          skel->children->next->next->next->next));
  kind = (svn_node_kind_t)n;

  *version_info = svn_wc_conflict_version_create2(repos_root,
                                                  NULL,
                                                  repos_relpath,
                                                  peg_rev,
                                                  kind,
                                                  result_pool);

  return SVN_NO_ERROR;
}