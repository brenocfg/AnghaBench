#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct write_rep_args {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; TYPE_1__* wb; } ;
struct TYPE_5__ {int /*<<< orphan*/  sha1_checksum_ctx; int /*<<< orphan*/  md5_checksum_ctx; int /*<<< orphan*/  txn_id; int /*<<< orphan*/  rep_key; int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  rep_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_write_rep(void *baton, trail_t *trail)
{
  struct write_rep_args *args = baton;

  SVN_ERR(rep_write(args->wb->fs,
                    args->wb->rep_key,
                    args->buf,
                    args->len,
                    args->wb->txn_id,
                    trail,
                    trail->pool));
  SVN_ERR(svn_checksum_update(args->wb->md5_checksum_ctx,
                              args->buf, args->len));
  SVN_ERR(svn_checksum_update(args->wb->sha1_checksum_ctx,
                              args->buf, args->len));
  return SVN_NO_ERROR;
}