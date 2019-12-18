#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct rep_write_baton {int /*<<< orphan*/  rep_key; int /*<<< orphan*/  fs; int /*<<< orphan*/  sha1_checksum; int /*<<< orphan*/  md5_checksum; } ;
struct TYPE_9__ {void* sha1_checksum; void* md5_checksum; } ;
typedef  TYPE_2__ representation_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 void* svn_checksum_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__read_rep (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_bdb__write_rep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_write_close_rep(void *baton, trail_t *trail)
{
  struct rep_write_baton *wb = baton;
  representation_t *rep;

  SVN_ERR(svn_fs_bdb__read_rep(&rep, wb->fs, wb->rep_key,
                               trail, trail->pool));
  rep->md5_checksum = svn_checksum_dup(wb->md5_checksum, trail->pool);
  rep->sha1_checksum = svn_checksum_dup(wb->sha1_checksum, trail->pool);
  return svn_fs_bdb__write_rep(wb->fs, wb->rep_key, rep,
                               trail, trail->pool);
}