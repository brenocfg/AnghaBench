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
typedef  int /*<<< orphan*/  tokens ;
typedef  int time_t ;
struct token {int HaveZone; long Timezone; int HaveYear; int HaveMonth; int HaveDay; int HaveTime; int HaveWeekDay; long tm_hour; long tm_min; int /*<<< orphan*/  DayNumber; int /*<<< orphan*/  DayOrdinal; int /*<<< orphan*/  DSTmode; int /*<<< orphan*/  RelMonth; scalar_t__ RelSeconds; scalar_t__ tm_sec; int /*<<< orphan*/  HaveRel; int /*<<< orphan*/  Seconds; int /*<<< orphan*/  Minutes; int /*<<< orphan*/  Hour; scalar_t__ Year; int /*<<< orphan*/  Day; scalar_t__ Month; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; struct token* tokenp; int /*<<< orphan*/  value; int /*<<< orphan*/  token; scalar_t__ tm_isdst; } ;
struct tm {int HaveZone; long Timezone; int HaveYear; int HaveMonth; int HaveDay; int HaveTime; int HaveWeekDay; long tm_hour; long tm_min; int /*<<< orphan*/  DayNumber; int /*<<< orphan*/  DayOrdinal; int /*<<< orphan*/  DSTmode; int /*<<< orphan*/  RelMonth; scalar_t__ RelSeconds; scalar_t__ tm_sec; int /*<<< orphan*/  HaveRel; int /*<<< orphan*/  Seconds; int /*<<< orphan*/  Minutes; int /*<<< orphan*/  Hour; scalar_t__ Year; int /*<<< orphan*/  Day; scalar_t__ Month; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; struct tm* tokenp; int /*<<< orphan*/  value; int /*<<< orphan*/  token; scalar_t__ tm_isdst; } ;
struct gdstate {int HaveZone; long Timezone; int HaveYear; int HaveMonth; int HaveDay; int HaveTime; int HaveWeekDay; long tm_hour; long tm_min; int /*<<< orphan*/  DayNumber; int /*<<< orphan*/  DayOrdinal; int /*<<< orphan*/  DSTmode; int /*<<< orphan*/  RelMonth; scalar_t__ RelSeconds; scalar_t__ tm_sec; int /*<<< orphan*/  HaveRel; int /*<<< orphan*/  Seconds; int /*<<< orphan*/  Minutes; int /*<<< orphan*/  Hour; scalar_t__ Year; int /*<<< orphan*/  Day; scalar_t__ Month; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; struct gdstate* tokenp; int /*<<< orphan*/  value; int /*<<< orphan*/  token; scalar_t__ tm_isdst; } ;
typedef  int /*<<< orphan*/  local ;
typedef  int /*<<< orphan*/  gmt ;
typedef  int /*<<< orphan*/  _gds ;

/* Variables and functions */
 int Convert (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSTmaybe ; 
 long HOUR ; 
 long MINUTE ; 
 int RelativeDate (int,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelativeMonth (int,long,int /*<<< orphan*/ ) ; 
 long difftm (struct token*,struct token*) ; 
 struct token* gmtime (int*) ; 
 struct token* localtime (int*) ; 
 int /*<<< orphan*/  memset (struct token*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nexttoken (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phrase (struct token*) ; 

time_t
__archive_get_date(time_t now, const char *p)
{
	struct token	tokens[256];
	struct gdstate	_gds;
	struct token	*lasttoken;
	struct gdstate	*gds;
	struct tm	local, *tm;
	struct tm	gmt, *gmt_ptr;
	time_t		Start;
	time_t		tod;
	long		tzone;

	/* Clear out the parsed token array. */
	memset(tokens, 0, sizeof(tokens));
	/* Initialize the parser state. */
	memset(&_gds, 0, sizeof(_gds));
	gds = &_gds;

	/* Look up the current time. */
	memset(&local, 0, sizeof(local));
	tm = localtime (&now);
	if (tm == NULL)
		return -1;
	local = *tm;

	/* Look up UTC if we can and use that to determine the current
	 * timezone offset. */
	memset(&gmt, 0, sizeof(gmt));
	gmt_ptr = gmtime (&now);
	if (gmt_ptr != NULL) {
		/* Copy, in case localtime and gmtime use the same buffer. */
		gmt = *gmt_ptr;
	}
	if (gmt_ptr != NULL)
		tzone = difftm (&gmt, &local);
	else
		/* This system doesn't understand timezones; fake it. */
		tzone = 0;
	if(local.tm_isdst)
		tzone += HOUR;

	/* Tokenize the input string. */
	lasttoken = tokens;
	while ((lasttoken->token = nexttoken(&p, &lasttoken->value)) != 0) {
		++lasttoken;
		if (lasttoken > tokens + 255)
			return -1;
	}
	gds->tokenp = tokens;

	/* Match phrases until we run out of input tokens. */
	while (gds->tokenp < lasttoken) {
		if (!phrase(gds))
			return -1;
	}

	/* Use current local timezone if none was specified. */
	if (!gds->HaveZone) {
		gds->Timezone = tzone;
		gds->DSTmode = DSTmaybe;
	}

	/* If a timezone was specified, use that for generating the default
	 * time components instead of the local timezone. */
	if (gds->HaveZone && gmt_ptr != NULL) {
		now -= gds->Timezone;
		gmt_ptr = gmtime (&now);
		if (gmt_ptr != NULL)
			local = *gmt_ptr;
		now += gds->Timezone;
	}

	if (!gds->HaveYear)
		gds->Year = local.tm_year + 1900;
	if (!gds->HaveMonth)
		gds->Month = local.tm_mon + 1;
	if (!gds->HaveDay)
		gds->Day = local.tm_mday;
	/* Note: No default for hour/min/sec; a specifier that just
	 * gives date always refers to 00:00 on that date. */

	/* If we saw more than one time, timezone, weekday, year, month,
	 * or day, then give up. */
	if (gds->HaveTime > 1 || gds->HaveZone > 1 || gds->HaveWeekDay > 1
	    || gds->HaveYear > 1 || gds->HaveMonth > 1 || gds->HaveDay > 1)
		return -1;

	/* Compute an absolute time based on whatever absolute information
	 * we collected. */
	if (gds->HaveYear || gds->HaveMonth || gds->HaveDay
	    || gds->HaveTime || gds->HaveWeekDay) {
		Start = Convert(gds->Month, gds->Day, gds->Year,
		    gds->Hour, gds->Minutes, gds->Seconds,
		    gds->Timezone, gds->DSTmode);
		if (Start < 0)
			return -1;
	} else {
		Start = now;
		if (!gds->HaveRel)
			Start -= local.tm_hour * HOUR + local.tm_min * MINUTE
			    + local.tm_sec;
	}

	/* Add the relative offset. */
	Start += gds->RelSeconds;
	Start += RelativeMonth(Start, gds->Timezone, gds->RelMonth);

	/* Adjust for day-of-week offsets. */
	if (gds->HaveWeekDay
	    && !(gds->HaveYear || gds->HaveMonth || gds->HaveDay)) {
		tod = RelativeDate(Start, gds->Timezone,
		    gds->DSTmode, gds->DayOrdinal, gds->DayNumber);
		Start += tod;
	}

	/* -1 is an error indicator, so return 0 instead of -1 if
	 * that's the actual time. */
	return Start == -1 ? 0 : Start;
}