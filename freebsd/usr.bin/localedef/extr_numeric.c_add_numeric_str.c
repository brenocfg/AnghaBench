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
struct TYPE_2__ {char* decimal_point; char* thousands_sep; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
#define  T_DECIMAL_POINT 129 
#define  T_THOUSANDS_SEP 128 
 int /*<<< orphan*/  free (char*) ; 
 int last_kw ; 
 TYPE_1__ numeric ; 
 char* to_mb_string (char*) ; 

void
add_numeric_str(wchar_t *wcs)
{
	char *str;

	if ((str = to_mb_string(wcs)) == NULL) {
		INTERR;
		return;
	}
	free(wcs);

	switch (last_kw) {
	case T_DECIMAL_POINT:
		numeric.decimal_point = str;
		break;
	case T_THOUSANDS_SEP:
		numeric.thousands_sep = str;
		break;
	default:
		free(str);
		INTERR;
		break;
	}
}