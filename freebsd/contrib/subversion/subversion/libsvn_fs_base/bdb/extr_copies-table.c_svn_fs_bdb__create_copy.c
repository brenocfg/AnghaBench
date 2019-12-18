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
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {char const* src_path; char const* src_txn_id; int /*<<< orphan*/  const* dst_noderev_id; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ copy_t ;
typedef  int /*<<< orphan*/  copy_kind_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * put_copy (int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_bdb__create_copy(svn_fs_t *fs,
                        const char *copy_id,
                        const char *src_path,
                        const char *src_txn_id,
                        const svn_fs_id_t *dst_noderev_id,
                        copy_kind_t kind,
                        trail_t *trail,
                        apr_pool_t *pool)
{
  copy_t copy;
  copy.kind = kind;
  copy.src_path = src_path;
  copy.src_txn_id = src_txn_id;
  copy.dst_noderev_id = dst_noderev_id;
  return put_copy(fs, &copy, copy_id, trail, pool);
}