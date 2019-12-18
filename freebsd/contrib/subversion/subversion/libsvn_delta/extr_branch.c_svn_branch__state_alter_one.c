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
typedef  int /*<<< orphan*/  svn_element__payload_t ;
typedef  int /*<<< orphan*/  svn_element__content_t ;
typedef  int /*<<< orphan*/  svn_branch__state_t ;
typedef  int /*<<< orphan*/  svn_branch__eid_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_branch__state_set_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_element__content_create (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_branch__state_alter_one(svn_branch__state_t *branch,
                            svn_branch__eid_t eid,
                            svn_branch__eid_t new_parent_eid,
                            const char *new_name,
                            const svn_element__payload_t *new_payload,
                            apr_pool_t *scratch_pool)
{
  svn_element__content_t *element
    = svn_element__content_create(new_parent_eid, new_name, new_payload,
                                  scratch_pool);

  SVN_ERR(svn_branch__state_set_element(branch, eid, element, scratch_pool));
  return SVN_NO_ERROR;
}