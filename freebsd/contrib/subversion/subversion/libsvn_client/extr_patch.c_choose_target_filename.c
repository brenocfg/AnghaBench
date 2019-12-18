#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* old_filename; char const* new_filename; scalar_t__ operation; } ;
typedef  TYPE_1__ svn_patch_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ svn_diff_op_moved ; 
 char const* svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_component_count (char const*) ; 

__attribute__((used)) static const char *
choose_target_filename(const svn_patch_t *patch)
{
  apr_size_t old;
  apr_size_t new;

  if (strcmp(patch->old_filename, "/dev/null") == 0)
    return patch->new_filename;
  if (strcmp(patch->new_filename, "/dev/null") == 0)
    return patch->old_filename;

  /* If the patch renames the target, use the old name while
   * applying hunks. The target will be renamed to the new name
   * after hunks have been applied. */
  if (patch->operation == svn_diff_op_moved)
    return patch->old_filename;

  old = svn_path_component_count(patch->old_filename);
  new = svn_path_component_count(patch->new_filename);

  if (old == new)
    {
      old = strlen(svn_dirent_basename(patch->old_filename, NULL));
      new = strlen(svn_dirent_basename(patch->new_filename, NULL));

      if (old == new)
        {
          old = strlen(patch->old_filename);
          new = strlen(patch->new_filename);
        }
    }

  return (old < new) ? patch->old_filename : patch->new_filename;
}