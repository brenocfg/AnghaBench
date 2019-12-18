#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_operation_t ;
typedef  int /*<<< orphan*/  svn_wc_conflict_version_t ;
struct TYPE_4__ {char const* mime_type; int /*<<< orphan*/  merged_file; int /*<<< orphan*/  their_abspath; int /*<<< orphan*/  base_abspath; int /*<<< orphan*/  my_abspath; int /*<<< orphan*/  const* src_right_version; int /*<<< orphan*/  const* src_left_version; int /*<<< orphan*/  operation; int /*<<< orphan*/  is_binary; } ;
typedef  TYPE_1__ svn_wc_conflict_description2_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_mime_type_is_binary (char const*) ; 
 int /*<<< orphan*/  svn_wc__conflict_read_text_conflict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_conflict_description_create_text2 (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_text_conflict_desc(svn_wc_conflict_description2_t **desc,
                        svn_wc__db_t *db,
                        const char *local_abspath,
                        const svn_skel_t *conflict_skel,
                        const char *mime_type,
                        svn_wc_operation_t operation,
                        const svn_wc_conflict_version_t *left_version,
                        const svn_wc_conflict_version_t *right_version,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  *desc = svn_wc_conflict_description_create_text2(local_abspath, result_pool);
  (*desc)->mime_type = mime_type;
  (*desc)->is_binary = mime_type ? svn_mime_type_is_binary(mime_type) : FALSE;
  (*desc)->operation = operation;
  (*desc)->src_left_version = left_version;
  (*desc)->src_right_version = right_version;

  SVN_ERR(svn_wc__conflict_read_text_conflict(&(*desc)->my_abspath,
                                              &(*desc)->base_abspath,
                                              &(*desc)->their_abspath,
                                              db, local_abspath,
                                              conflict_skel,
                                              result_pool, scratch_pool));
  (*desc)->merged_file = apr_pstrdup(result_pool, local_abspath);

  return SVN_NO_ERROR;
}