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
struct TYPE_4__ {void* property_name; int /*<<< orphan*/  kind; int /*<<< orphan*/  node_kind; void* local_abspath; } ;
typedef  TYPE_1__ svn_wc_conflict_description2_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int /*<<< orphan*/ ) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_wc_conflict_kind_property ; 

svn_wc_conflict_description2_t *
svn_wc_conflict_description_create_prop2(const char *local_abspath,
                                         svn_node_kind_t node_kind,
                                         const char *property_name,
                                         apr_pool_t *result_pool)
{
  svn_wc_conflict_description2_t *conflict;

  SVN_ERR_ASSERT_NO_RETURN(svn_dirent_is_absolute(local_abspath));

  conflict = apr_pcalloc(result_pool, sizeof(*conflict));
  conflict->local_abspath = apr_pstrdup(result_pool, local_abspath);
  conflict->node_kind = node_kind;
  conflict->kind = svn_wc_conflict_kind_property;
  conflict->property_name = apr_pstrdup(result_pool, property_name);
  return conflict;
}