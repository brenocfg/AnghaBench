#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * db_txn; TYPE_3__* fs; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ trail_t ;
struct TYPE_12__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_13__ {scalar_t__ in_txn_trail; TYPE_1__* bdb; } ;
typedef  TYPE_4__ base_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* txn_begin ) (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_5__* env; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_WRAP (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
begin_trail(trail_t **trail_p,
            svn_fs_t *fs,
            svn_boolean_t use_txn,
            apr_pool_t *pool)
{
  base_fs_data_t *bfd = fs->fsap_data;
  trail_t *trail = apr_pcalloc(pool, sizeof(*trail));

  trail->pool = svn_pool_create(pool);
  trail->fs = fs;
  if (use_txn)
    {
      /* [*]
         If we're already inside a trail operation, abort() -- this is
         a coding problem (and will likely hang the repository anyway). */
      SVN_ERR_ASSERT(! bfd->in_txn_trail);

      SVN_ERR(BDB_WRAP(fs, N_("beginning Berkeley DB transaction"),
                       bfd->bdb->env->txn_begin(bfd->bdb->env, 0,
                                                &trail->db_txn, 0)));
      bfd->in_txn_trail = TRUE;
    }
  else
    {
      trail->db_txn = NULL;
    }

  *trail_p = trail;
  return SVN_NO_ERROR;
}