#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* data; } ;
typedef  TYPE_2__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {TYPE_1__* wrapped_editor; int /*<<< orphan*/  out; } ;
struct dir_baton {int /*<<< orphan*/  wrapped_dir_baton; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* change_dir_prop ) (int /*<<< orphan*/ ,char const*,TYPE_2__ const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,char*) ; 
 int /*<<< orphan*/  write_indent (struct edit_baton*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
change_dir_prop(void *dir_baton,
                const char *name,
                const svn_string_t *value,
                apr_pool_t *pool)
{
  struct dir_baton *db = dir_baton;
  struct edit_baton *eb = db->edit_baton;

  SVN_ERR(write_indent(eb, pool));
  SVN_ERR(svn_stream_printf(eb->out, pool, "change_dir_prop : %s -> %s\n",
                            name, value ? value->data : "<deleted>"));

  SVN_ERR(eb->wrapped_editor->change_dir_prop(db->wrapped_dir_baton,
                                              name,
                                              value,
                                              pool));

  return SVN_NO_ERROR;
}