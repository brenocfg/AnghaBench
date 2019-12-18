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
struct TYPE_2__ {char* int_curr_symbol; char* currency_symbol; char* mon_decimal_point; char* mon_thousands_sep; char* positive_sign; char* negative_sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
#define  T_CURRENCY_SYMBOL 133 
#define  T_INT_CURR_SYMBOL 132 
#define  T_MON_DECIMAL_POINT 131 
#define  T_MON_THOUSANDS_SEP 130 
#define  T_NEGATIVE_SIGN 129 
#define  T_POSITIVE_SIGN 128 
 int /*<<< orphan*/  free (char*) ; 
 int last_kw ; 
 TYPE_1__ mon ; 
 char* to_mb_string (char*) ; 

void
add_monetary_str(wchar_t *wcs)
{
	char *str;

	if ((str = to_mb_string(wcs)) == NULL) {
		INTERR;
		return;
	}
	free(wcs);
	switch (last_kw) {
	case T_INT_CURR_SYMBOL:
		mon.int_curr_symbol = str;
		break;
	case T_CURRENCY_SYMBOL:
		mon.currency_symbol = str;
		break;
	case T_MON_DECIMAL_POINT:
		mon.mon_decimal_point = str;
		break;
	case T_MON_THOUSANDS_SEP:
		mon.mon_thousands_sep = str;
		break;
	case T_POSITIVE_SIGN:
		mon.positive_sign = str;
		break;
	case T_NEGATIVE_SIGN:
		mon.negative_sign = str;
		break;
	default:
		free(str);
		INTERR;
		break;
	}
}