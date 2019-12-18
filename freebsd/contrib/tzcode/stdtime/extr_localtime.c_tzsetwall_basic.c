#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _RWLOCK_RDLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _RWLOCK_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _RWLOCK_WRLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  gmtload (int /*<<< orphan*/ *) ; 
 int lcl_is_set ; 
 int /*<<< orphan*/  lcl_rwlock ; 
 int /*<<< orphan*/ * lclptr ; 
 int /*<<< orphan*/  settzname () ; 
 scalar_t__ tzload (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tzsetwall_basic(int rdlocked)
{
	if (!rdlocked)
		_RWLOCK_RDLOCK(&lcl_rwlock);
	if (lcl_is_set < 0) {
		if (!rdlocked)
			_RWLOCK_UNLOCK(&lcl_rwlock);
		return;
	}
	_RWLOCK_UNLOCK(&lcl_rwlock);

	_RWLOCK_WRLOCK(&lcl_rwlock);
	lcl_is_set = -1;

#ifdef ALL_STATE
	if (lclptr == NULL) {
		lclptr = calloc(1, sizeof *lclptr);
		if (lclptr == NULL) {
			settzname();	/* all we can do */
			_RWLOCK_UNLOCK(&lcl_rwlock);
			if (rdlocked)
				_RWLOCK_RDLOCK(&lcl_rwlock);
			return;
		}
	}
#endif /* defined ALL_STATE */
	if (tzload((char *) NULL, lclptr, TRUE) != 0)
		gmtload(lclptr);
	settzname();
	_RWLOCK_UNLOCK(&lcl_rwlock);

	if (rdlocked)
		_RWLOCK_RDLOCK(&lcl_rwlock);
}