#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct state {int /*<<< orphan*/  chars; TYPE_1__* ttis; scalar_t__ typecnt; scalar_t__ timecnt; scalar_t__ leapcnt; } ;
struct TYPE_2__ {scalar_t__ tt_abbrind; scalar_t__ tt_gmtoff; scalar_t__ tt_isdst; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _RWLOCK_RDLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _RWLOCK_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _RWLOCK_WRLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 
 char* getenv (char*) ; 
 char const* gmt ; 
 int /*<<< orphan*/  gmtload (struct state*) ; 
 int /*<<< orphan*/  lcl_TZname ; 
 int lcl_is_set ; 
 int /*<<< orphan*/  lcl_rwlock ; 
 struct state* lclptr ; 
 int /*<<< orphan*/  settzname () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ tzload (char const*,struct state*,int /*<<< orphan*/ ) ; 
 scalar_t__ tzparse (char const*,struct state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tzsetwall_basic (int) ; 

__attribute__((used)) static void
tzset_basic(int rdlocked)
{
	const char *	name;

	name = getenv("TZ");
	if (name == NULL) {
		tzsetwall_basic(rdlocked);
		return;
	}

	if (!rdlocked)
		_RWLOCK_RDLOCK(&lcl_rwlock);
	if (lcl_is_set > 0 && strcmp(lcl_TZname, name) == 0) {
		if (!rdlocked)
			_RWLOCK_UNLOCK(&lcl_rwlock);
		return;
	}
	_RWLOCK_UNLOCK(&lcl_rwlock);

	_RWLOCK_WRLOCK(&lcl_rwlock);
	lcl_is_set = strlen(name) < sizeof lcl_TZname;
	if (lcl_is_set)
		(void) strcpy(lcl_TZname, name);

#ifdef ALL_STATE
	if (lclptr == NULL) {
		lclptr = (struct state *) calloc(1, sizeof *lclptr);
		if (lclptr == NULL) {
			settzname();	/* all we can do */
			_RWLOCK_UNLOCK(&lcl_rwlock);
			if (rdlocked)
				_RWLOCK_RDLOCK(&lcl_rwlock);
			return;
		}
	}
#endif /* defined ALL_STATE */
	if (*name == '\0') {
		/*
		** User wants it fast rather than right.
		*/
		lclptr->leapcnt = 0;		/* so, we're off a little */
		lclptr->timecnt = 0;
		lclptr->typecnt = 0;
		lclptr->ttis[0].tt_isdst = 0;
		lclptr->ttis[0].tt_gmtoff = 0;
		lclptr->ttis[0].tt_abbrind = 0;
		(void) strcpy(lclptr->chars, gmt);
	} else if (tzload(name, lclptr, TRUE) != 0)
		if (name[0] == ':' || tzparse(name, lclptr, FALSE) != 0)
			(void) gmtload(lclptr);
	settzname();
	_RWLOCK_UNLOCK(&lcl_rwlock);

	if (rdlocked)
		_RWLOCK_RDLOCK(&lcl_rwlock);
}