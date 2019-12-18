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
typedef  void dmu_buf_user_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;
struct TYPE_3__ {void* db_user; int /*<<< orphan*/  db_mtx; } ;
typedef  TYPE_1__ dmu_buf_impl_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBVU_NOT_EVICTING ; 
 int /*<<< orphan*/  dbuf_verify_user (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void *
dmu_buf_replace_user(dmu_buf_t *db_fake, dmu_buf_user_t *old_user,
    dmu_buf_user_t *new_user)
{
	dmu_buf_impl_t *db = (dmu_buf_impl_t *)db_fake;

	mutex_enter(&db->db_mtx);
	dbuf_verify_user(db, DBVU_NOT_EVICTING);
	if (db->db_user == old_user)
		db->db_user = new_user;
	else
		old_user = db->db_user;
	dbuf_verify_user(db, DBVU_NOT_EVICTING);
	mutex_exit(&db->db_mtx);

	return (old_user);
}