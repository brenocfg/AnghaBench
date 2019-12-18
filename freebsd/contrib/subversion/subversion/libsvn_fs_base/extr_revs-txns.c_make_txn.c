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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_4__ {char const* id; int /*<<< orphan*/ * fsap_data; int /*<<< orphan*/ * vtable; int /*<<< orphan*/  base_rev; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  txn_vtable ; 

__attribute__((used)) static svn_fs_txn_t *
make_txn(svn_fs_t *fs,
         const char *id,
         svn_revnum_t base_rev,
         apr_pool_t *pool)
{
  svn_fs_txn_t *txn = apr_pcalloc(pool, sizeof(*txn));

  txn->fs = fs;
  txn->id = id;
  txn->base_rev = base_rev;
  txn->vtable = &txn_vtable;
  txn->fsap_data = NULL;

  return txn;
}