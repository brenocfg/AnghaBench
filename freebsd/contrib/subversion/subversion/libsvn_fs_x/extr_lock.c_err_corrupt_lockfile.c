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

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static svn_error_t *
err_corrupt_lockfile(const char *fs_path,
                     const char *path)
{
  return
    svn_error_createf(
     SVN_ERR_FS_CORRUPT, 0,
     _("Corrupt lockfile for path '%s' in filesystem '%s'"),
     path, fs_path);
}