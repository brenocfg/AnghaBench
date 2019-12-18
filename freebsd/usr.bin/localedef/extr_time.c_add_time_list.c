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
typedef  char wchar_t ;
struct TYPE_2__ {char* am; char* pm; int /*<<< orphan*/  weekday; int /*<<< orphan*/  wday; int /*<<< orphan*/  month; int /*<<< orphan*/  mon; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
#define  T_ABDAY 134 
#define  T_ABMON 133 
#define  T_ALT_DIGITS 132 
#define  T_AM_PM 131 
#define  T_DAY 130 
#define  T_ERA 129 
#define  T_MON 128 
 int /*<<< orphan*/  add_list (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int last_kw ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__ tm ; 
 char* to_mb_string (char*) ; 

void
add_time_list(wchar_t *wcs)
{
	char *str;

	if ((str = to_mb_string(wcs)) == NULL) {
		INTERR;
		return;
	}
	free(wcs);

	switch (last_kw) {
	case T_ABMON:
		add_list(tm.mon, str, 12);
		break;
	case T_MON:
		add_list(tm.month, str, 12);
		break;
	case T_ABDAY:
		add_list(tm.wday, str, 7);
		break;
	case T_DAY:
		add_list(tm.weekday, str, 7);
		break;
	case T_AM_PM:
		if (tm.am == NULL) {
			tm.am = str;
		} else if (tm.pm == NULL) {
			tm.pm = str;
		} else {
			fprintf(stderr,"too many list elements");
			free(str);
		}
		break;
	case T_ALT_DIGITS:
	case T_ERA:
		free(str);
		break;
	default:
		free(str);
		INTERR;
		break;
	}
}