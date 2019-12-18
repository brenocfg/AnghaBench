#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_name_t ;
struct TYPE_8__ {TYPE_3__* zc_zap; int /*<<< orphan*/  zc_cd; int /*<<< orphan*/  zc_hash; int /*<<< orphan*/  zc_zapobj; int /*<<< orphan*/  zc_objset; } ;
typedef  TYPE_1__ zap_cursor_t ;
struct TYPE_9__ {int /*<<< orphan*/  mze_cd; int /*<<< orphan*/  mze_hash; } ;
typedef  TYPE_2__ mzap_ent_t ;
typedef  int /*<<< orphan*/  matchtype_t ;
struct TYPE_10__ {int /*<<< orphan*/  zap_rwlock; int /*<<< orphan*/  zap_ismicro; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int fzap_cursor_move_to_key (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* mze_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int zap_lockdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/ * zap_name_alloc (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_name_free (int /*<<< orphan*/ *) ; 

int
zap_cursor_move_to_key(zap_cursor_t *zc, const char *name, matchtype_t mt)
{
	int err = 0;
	mzap_ent_t *mze;
	zap_name_t *zn;

	if (zc->zc_zap == NULL) {
		err = zap_lockdir(zc->zc_objset, zc->zc_zapobj, NULL,
		    RW_READER, TRUE, FALSE, FTAG, &zc->zc_zap);
		if (err)
			return (err);
	} else {
		rw_enter(&zc->zc_zap->zap_rwlock, RW_READER);
	}

	zn = zap_name_alloc(zc->zc_zap, name, mt);
	if (zn == NULL) {
		rw_exit(&zc->zc_zap->zap_rwlock);
		return (SET_ERROR(ENOTSUP));
	}

	if (!zc->zc_zap->zap_ismicro) {
		err = fzap_cursor_move_to_key(zc, zn);
	} else {
		mze = mze_find(zn);
		if (mze == NULL) {
			err = SET_ERROR(ENOENT);
			goto out;
		}
		zc->zc_hash = mze->mze_hash;
		zc->zc_cd = mze->mze_cd;
	}

out:
	zap_name_free(zn);
	rw_exit(&zc->zc_zap->zap_rwlock);
	return (err);
}