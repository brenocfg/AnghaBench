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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  void* svn_boolean_t ;
struct TYPE_3__ {void* prop_mod; void* text_mod; int /*<<< orphan*/  kind; int /*<<< orphan*/  const* noderev_id; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ change_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_fs__canonicalize_abspath (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_bdb__changes_add (int /*<<< orphan*/ *,char const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_change(svn_fs_t *fs,
           const char *txn_id,
           const char *path,
           const svn_fs_id_t *noderev_id,
           svn_fs_path_change_kind_t change_kind,
           svn_boolean_t text_mod,
           svn_boolean_t prop_mod,
           trail_t *trail,
           apr_pool_t *pool)
{
  change_t change;
  change.path = svn_fs__canonicalize_abspath(path, pool);
  change.noderev_id = noderev_id;
  change.kind = change_kind;
  change.text_mod = text_mod;
  change.prop_mod = prop_mod;
  return svn_fs_bdb__changes_add(fs, txn_id, &change, trail, pool);
}