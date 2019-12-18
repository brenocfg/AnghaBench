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
struct dir_baton_t {scalar_t__ deletes; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_make (int /*<<< orphan*/ ) ; 
 char* svn_dirent_basename (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,char const*,char*) ; 

__attribute__((used)) static svn_error_t *
delete_entry(const char *path,
             svn_revnum_t base_revision,
             void *parent_baton,
             apr_pool_t *pool)
{
  struct dir_baton_t *pb = parent_baton;
  const char *name = svn_dirent_basename(path, pb->pool);

  if (!pb->deletes)
    pb->deletes = apr_hash_make(pb->pool);

  svn_hash_sets(pb->deletes, name, "");
  return SVN_NO_ERROR;
}