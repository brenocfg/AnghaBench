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
struct TYPE_2__ {char* c_fmt; char* x_fmt; char* X_fmt; char* ampm_fmt; char* date_fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
#define  T_DATE_FMT 135 
#define  T_D_FMT 134 
#define  T_D_T_FMT 133 
#define  T_ERA_D_FMT 132 
#define  T_ERA_D_T_FMT 131 
#define  T_ERA_T_FMT 130 
#define  T_T_FMT 129 
#define  T_T_FMT_AMPM 128 
 int /*<<< orphan*/  free (char*) ; 
 int last_kw ; 
 TYPE_1__ tm ; 
 char* to_mb_string (char*) ; 

void
add_time_str(wchar_t *wcs)
{
	char	*str;

	if ((str = to_mb_string(wcs)) == NULL) {
		INTERR;
		return;
	}
	free(wcs);

	switch (last_kw) {
	case T_D_T_FMT:
		tm.c_fmt = str;
		break;
	case T_D_FMT:
		tm.x_fmt = str;
		break;
	case T_T_FMT:
		tm.X_fmt = str;
		break;
	case T_T_FMT_AMPM:
		tm.ampm_fmt = str;
		break;
	case T_DATE_FMT:
		/*
		 * This one is a Solaris extension, Too bad date just
		 * doesn't use %c, which would be simpler.
		 */
		tm.date_fmt = str;
		break;
	case T_ERA_D_FMT:
	case T_ERA_T_FMT:
	case T_ERA_D_T_FMT:
		/* Silently ignore it. */
		free(str);
		break;
	default:
		free(str);
		INTERR;
		break;
	}
}