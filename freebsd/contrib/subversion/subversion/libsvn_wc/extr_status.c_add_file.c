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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {void* added; } ;
struct dir_baton {void* text_changed; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 struct file_baton* make_file_baton (struct dir_baton*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_file(const char *path,
         void *parent_baton,
         const char *copyfrom_path,
         svn_revnum_t copyfrom_revision,
         apr_pool_t *pool,
         void **file_baton)
{
  struct dir_baton *pb = parent_baton;
  struct file_baton *new_fb = make_file_baton(pb, path, pool);

  /* Mark parent dir as changed */
  pb->text_changed = TRUE;

  /* Make this file as added. */
  new_fb->added = TRUE;

  *file_baton = new_fb;
  return SVN_NO_ERROR;
}