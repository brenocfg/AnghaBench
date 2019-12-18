#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_baton {int /*<<< orphan*/  wrapped_baton; struct edit_baton* edit_baton; } ;
struct edit_baton {TYPE_1__* wrapped_editor; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* delete_entry ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ okay_to_edit (struct edit_baton*,struct node_baton*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 

__attribute__((used)) static svn_error_t *
delete_entry(const char *path,
             svn_revnum_t base_revision,
             void *parent_baton,
             apr_pool_t *pool)
{
  struct node_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;

  /* ### FIXME: We don't know the type of the entry, which ordinarily
     doesn't matter, but is a key (*the* key, in fact) distinction
     between depth "files" and depths "immediates".  If the server is
     telling us to delete a subdirectory and our requested depth was
     "immediates", that's fine; if our requested depth was "files",
     though, this deletion shouldn't survive filtering.  For now,
     we'll claim to our helper function that the to-be-deleted thing
     is a file because that's the conservative route to take. */
  if (okay_to_edit(eb, pb, svn_node_file))
    SVN_ERR(eb->wrapped_editor->delete_entry(path, base_revision,
                                             pb->wrapped_baton, pool));

  return SVN_NO_ERROR;
}