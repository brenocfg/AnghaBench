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
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_3__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_base__dag_dir_entries (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static svn_error_t *
dir_entry_id_from_node(const svn_fs_id_t **id_p,
                       dag_node_t *parent,
                       const char *name,
                       trail_t *trail,
                       apr_pool_t *pool)
{
  apr_hash_t *entries;
  svn_fs_dirent_t *dirent;

  SVN_ERR(svn_fs_base__dag_dir_entries(&entries, parent, trail, pool));
  if (entries)
    dirent = svn_hash_gets(entries, name);
  else
    dirent = NULL;

  *id_p = dirent ? dirent->id : NULL;
  return SVN_NO_ERROR;
}