#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_8__ {int /*<<< orphan*/  chunk_index; int /*<<< orphan*/  item_index; scalar_t__ revision; } ;
typedef  TYPE_2__ svn_fs_x__window_cache_key_t ;
struct TYPE_7__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
struct TYPE_9__ {int /*<<< orphan*/  chunk_index; TYPE_1__ rep_id; } ;
typedef  TYPE_3__ rep_state_t ;
typedef  scalar_t__ apr_uint32_t ;

/* Variables and functions */
 scalar_t__ APR_UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_fs_x__window_cache_key_t *
get_window_key(svn_fs_x__window_cache_key_t *key,
               rep_state_t *rs)
{
  svn_revnum_t revision = svn_fs_x__get_revnum(rs->rep_id.change_set);
  assert(revision <= APR_UINT32_MAX);

  key->revision = (apr_uint32_t)revision;
  key->item_index = rs->rep_id.number;
  key->chunk_index = rs->chunk_index;

  return key;
}