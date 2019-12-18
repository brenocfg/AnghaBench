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
struct ttinfo {size_t tt_isdst; size_t tt_abbrind; int /*<<< orphan*/  tt_gmtoff; } ;
struct state {int typecnt; size_t* types; char* chars; int charcnt; struct ttinfo* ttis; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRANDPARENTED ; 
 int /*<<< orphan*/  TZ_ABBR_CHAR_SET ; 
 char TZ_ABBR_ERR_CHAR ; 
 scalar_t__ TZ_ABBR_MAX_LEN ; 
 int /*<<< orphan*/  altzone ; 
 int daylight ; 
 char* gmt ; 
 struct state* lclptr ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  timezone ; 
 char** tzname ; 
 char* wildabbr ; 

__attribute__((used)) static void
settzname(void)
{
	struct state * 	sp = lclptr;
	int			i;

	tzname[0] = wildabbr;
	tzname[1] = wildabbr;
#ifdef USG_COMPAT
	daylight = 0;
	timezone = 0;
#endif /* defined USG_COMPAT */
#ifdef ALTZONE
	altzone = 0;
#endif /* defined ALTZONE */
#ifdef ALL_STATE
	if (sp == NULL) {
		tzname[0] = tzname[1] = gmt;
		return;
	}
#endif /* defined ALL_STATE */
	/*
	** And to get the latest zone names into tzname. . .
	*/
	for (i = 0; i < sp->typecnt; ++i) {
		const struct ttinfo * const ttisp = &sp->ttis[sp->types[i]];

		tzname[ttisp->tt_isdst] =
			&sp->chars[ttisp->tt_abbrind];
#ifdef USG_COMPAT
		if (ttisp->tt_isdst)
			daylight = 1;
		if (!ttisp->tt_isdst)
			timezone = -(ttisp->tt_gmtoff);
#endif /* defined USG_COMPAT */
#ifdef ALTZONE
		if (ttisp->tt_isdst)
			altzone = -(ttisp->tt_gmtoff);
#endif /* defined ALTZONE */
	}
	/*
	** Finally, scrub the abbreviations.
	** First, replace bogus characters.
	*/
	for (i = 0; i < sp->charcnt; ++i)
		if (strchr(TZ_ABBR_CHAR_SET, sp->chars[i]) == NULL)
			sp->chars[i] = TZ_ABBR_ERR_CHAR;
	/*
	** Second, truncate long abbreviations.
	*/
	for (i = 0; i < sp->typecnt; ++i) {
		register const struct ttinfo * const	ttisp = &sp->ttis[i];
		register char *				cp = &sp->chars[ttisp->tt_abbrind];

		if (strlen(cp) > TZ_ABBR_MAX_LEN &&
			strcmp(cp, GRANDPARENTED) != 0)
				*(cp + TZ_ABBR_MAX_LEN) = '\0';
	}
}