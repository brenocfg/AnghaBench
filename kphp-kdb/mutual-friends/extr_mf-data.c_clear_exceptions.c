#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  new_exceptions; scalar_t__ metafile_len; int /*<<< orphan*/ * metafile; } ;
typedef  TYPE_2__ user ;
struct lev_mf_clear_exceptions {int /*<<< orphan*/  user_id; } ;
struct TYPE_11__ {int user_cnt; TYPE_1__* user_index; } ;
struct TYPE_9__ {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ NOAIO ; 
 int /*<<< orphan*/  add_user_used (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_readed ; 
 int /*<<< orphan*/  chg_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* conv_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_user_used (TYPE_2__*) ; 
 TYPE_5__ header ; 
 scalar_t__ index_mode ; 
 int /*<<< orphan*/  load_user_metafile (TYPE_2__*,int,int) ; 
 int local_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfree (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  user_loaded (TYPE_2__*) ; 

int clear_exceptions (struct lev_mf_clear_exceptions *E) {
  user *u = conv_uid (E->user_id);
  int local_id = local_uid (E->user_id);

  if (u == NULL) {
    return 0;
  }

  load_user_metafile (u, local_id, NOAIO || index_mode || !binlog_readed);

  if (!user_loaded (u)) {
    return -2;
  }

  del_user_used (u);
  add_user_used (u);

  if (u->metafile != NULL) {
    assert (1 <= local_id && local_id <= header.user_cnt);

    qfree (u->metafile, u->metafile_len);
    u->metafile = NULL;
    u->metafile_len = 0;
    header.user_index[local_id].size = 0;
  }
  chg_free (&u->new_exceptions);
  return 1;
}