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
typedef  int /*<<< orphan*/  const svn_repos_parse_fns3_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VTABLE_ENTRY (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_textdelta ; 
 int /*<<< orphan*/  const* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_node ; 
 int /*<<< orphan*/  close_revision ; 
 int /*<<< orphan*/  delete_node_property ; 
 int /*<<< orphan*/  magic_header_record ; 
 int /*<<< orphan*/  new_node_record ; 
 int /*<<< orphan*/  new_revision_record ; 
 int /*<<< orphan*/  remove_node_props ; 
 int /*<<< orphan*/  set_fulltext ; 
 int /*<<< orphan*/  set_node_property ; 
 int /*<<< orphan*/  set_revision_property ; 
 int /*<<< orphan*/  uuid_record ; 

__attribute__((used)) static const svn_repos_parse_fns3_t *
complete_vtable(const svn_repos_parse_fns3_t *provided,
                apr_pool_t *result_pool)
{
  svn_repos_parse_fns3_t *completed = apr_pcalloc(result_pool,
                                                  sizeof(*completed));

  SET_VTABLE_ENTRY(completed, provided, magic_header_record);
  SET_VTABLE_ENTRY(completed, provided, uuid_record);
  SET_VTABLE_ENTRY(completed, provided, new_revision_record);
  SET_VTABLE_ENTRY(completed, provided, new_node_record);
  SET_VTABLE_ENTRY(completed, provided, set_revision_property);
  SET_VTABLE_ENTRY(completed, provided, set_node_property);
  SET_VTABLE_ENTRY(completed, provided, delete_node_property);
  SET_VTABLE_ENTRY(completed, provided, remove_node_props);
  SET_VTABLE_ENTRY(completed, provided, set_fulltext);
  SET_VTABLE_ENTRY(completed, provided, apply_textdelta);
  SET_VTABLE_ENTRY(completed, provided, close_node);
  SET_VTABLE_ENTRY(completed, provided, close_revision);

  return completed;
}