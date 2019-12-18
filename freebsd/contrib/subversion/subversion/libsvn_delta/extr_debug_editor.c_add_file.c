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
struct file_baton {struct edit_baton* edit_baton; int /*<<< orphan*/  wrapped_file_baton; } ;
struct edit_baton {TYPE_1__* wrapped_editor; int /*<<< orphan*/  indent_level; int /*<<< orphan*/  out; } ;
struct dir_baton {int /*<<< orphan*/  wrapped_dir_baton; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* add_file ) (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct file_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_indent (struct edit_baton*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_file(const char *path,
         void *parent_baton,
         const char *copyfrom_path,
         svn_revnum_t copyfrom_revision,
         apr_pool_t *pool,
         void **file_baton)
{
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  struct file_baton *fb = apr_palloc(pool, sizeof(*fb));

  SVN_ERR(write_indent(eb, pool));
  SVN_ERR(svn_stream_printf(eb->out, pool,
                            "add_file : '%s' [from '%s':%ld]\n",
                            path, copyfrom_path, copyfrom_revision));

  eb->indent_level++;

  SVN_ERR(eb->wrapped_editor->add_file(path,
                                       pb->wrapped_dir_baton,
                                       copyfrom_path,
                                       copyfrom_revision,
                                       pool,
                                       &fb->wrapped_file_baton));

  fb->edit_baton = eb;
  *file_baton = fb;

  return SVN_NO_ERROR;
}