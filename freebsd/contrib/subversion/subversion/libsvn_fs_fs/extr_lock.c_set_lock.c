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
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  digest_path_from_path (char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_digest_file (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_digest_file (int /*<<< orphan*/ *,TYPE_1__*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_lock(const char *fs_path,
         svn_lock_t *lock,
         const char *perms_reference,
         apr_pool_t *pool)
{
  const char *digest_path;
  apr_hash_t *children;

  SVN_ERR(digest_path_from_path(&digest_path, fs_path, lock->path, pool));

  /* We could get away without reading the file as children should
     always come back empty. */
  SVN_ERR(read_digest_file(&children, NULL, fs_path, digest_path, pool));

  SVN_ERR(write_digest_file(children, lock, fs_path, digest_path,
                            perms_reference, pool));

  return SVN_NO_ERROR;
}