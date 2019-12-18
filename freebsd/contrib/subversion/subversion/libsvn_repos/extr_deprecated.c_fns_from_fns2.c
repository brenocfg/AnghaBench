#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  close_revision; int /*<<< orphan*/  close_node; int /*<<< orphan*/  set_fulltext; int /*<<< orphan*/  remove_node_props; int /*<<< orphan*/  set_node_property; int /*<<< orphan*/  set_revision_property; int /*<<< orphan*/  new_node_record; int /*<<< orphan*/  uuid_record; int /*<<< orphan*/  new_revision_record; } ;
typedef  TYPE_1__ svn_repos_parser_fns_t ;
struct TYPE_7__ {int /*<<< orphan*/  close_revision; int /*<<< orphan*/  close_node; int /*<<< orphan*/  set_fulltext; int /*<<< orphan*/  remove_node_props; int /*<<< orphan*/  set_node_property; int /*<<< orphan*/  set_revision_property; int /*<<< orphan*/  new_node_record; int /*<<< orphan*/  uuid_record; int /*<<< orphan*/  new_revision_record; } ;
typedef  TYPE_2__ svn_repos_parse_fns2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_repos_parser_fns_t *
fns_from_fns2(const svn_repos_parse_fns2_t *fns2,
              apr_pool_t *pool)
{
  svn_repos_parser_fns_t *fns;

  fns = apr_palloc(pool, sizeof(*fns));
  fns->new_revision_record = fns2->new_revision_record;
  fns->uuid_record = fns2->uuid_record;
  fns->new_node_record = fns2->new_node_record;
  fns->set_revision_property = fns2->set_revision_property;
  fns->set_node_property = fns2->set_node_property;
  fns->remove_node_props = fns2->remove_node_props;
  fns->set_fulltext = fns2->set_fulltext;
  fns->close_node = fns2->close_node;
  fns->close_revision = fns2->close_revision;
  return fns;
}