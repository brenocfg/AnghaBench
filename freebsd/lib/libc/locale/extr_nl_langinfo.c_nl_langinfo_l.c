#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int nl_item ;
typedef  TYPE_2__* locale_t ;
struct TYPE_24__ {scalar_t__ thousands_sep; scalar_t__ decimal_point; } ;
struct TYPE_23__ {scalar_t__ md_order; scalar_t__* alt_month; scalar_t__* mon; scalar_t__* month; scalar_t__* wday; scalar_t__* weekday; scalar_t__ pm; scalar_t__ am; scalar_t__ ampm_fmt; scalar_t__ X_fmt; scalar_t__ x_fmt; scalar_t__ c_fmt; } ;
struct TYPE_22__ {char p_cs_precedes; char n_cs_precedes; } ;
struct TYPE_21__ {char* csym; } ;
struct TYPE_20__ {char* __encoding; } ;
struct TYPE_19__ {TYPE_1__* runes; } ;
struct TYPE_18__ {scalar_t__ nostr; scalar_t__ yesstr; scalar_t__ noexpr; scalar_t__ yesexpr; } ;
struct TYPE_17__ {char* mon_decimal_point; scalar_t__ currency_symbol; } ;

/* Variables and functions */
#define  ABDAY_1 197 
#define  ABDAY_2 196 
#define  ABDAY_3 195 
#define  ABDAY_4 194 
#define  ABDAY_5 193 
#define  ABDAY_6 192 
#define  ABDAY_7 191 
#define  ABMON_1 190 
#define  ABMON_10 189 
#define  ABMON_11 188 
#define  ABMON_12 187 
#define  ABMON_2 186 
#define  ABMON_3 185 
#define  ABMON_4 184 
#define  ABMON_5 183 
#define  ABMON_6 182 
#define  ABMON_7 181 
#define  ABMON_8 180 
#define  ABMON_9 179 
#define  ALTMON_1 178 
#define  ALTMON_10 177 
#define  ALTMON_11 176 
#define  ALTMON_12 175 
#define  ALTMON_2 174 
#define  ALTMON_3 173 
#define  ALTMON_4 172 
#define  ALTMON_5 171 
#define  ALTMON_6 170 
#define  ALTMON_7 169 
#define  ALTMON_8 168 
#define  ALTMON_9 167 
#define  ALT_DIGITS 166 
#define  AM_STR 165 
 char CHAR_MAX ; 
#define  CODESET 164 
#define  CRNCYSTR 163 
#define  DAY_1 162 
#define  DAY_2 161 
#define  DAY_3 160 
#define  DAY_4 159 
#define  DAY_5 158 
#define  DAY_6 157 
#define  DAY_7 156 
#define  D_FMT 155 
#define  D_MD_ORDER 154 
#define  D_T_FMT 153 
#define  ERA 152 
#define  ERA_D_FMT 151 
#define  ERA_D_T_FMT 150 
#define  ERA_T_FMT 149 
 int /*<<< orphan*/  FIX_LOCALE (TYPE_2__*) ; 
#define  MON_1 148 
#define  MON_10 147 
#define  MON_11 146 
#define  MON_12 145 
#define  MON_2 144 
#define  MON_3 143 
#define  MON_4 142 
#define  MON_5 141 
#define  MON_6 140 
#define  MON_7 139 
#define  MON_8 138 
#define  MON_9 137 
#define  NOEXPR 136 
#define  NOSTR 135 
#define  PM_STR 134 
#define  RADIXCHAR 133 
#define  THOUSEP 132 
#define  T_FMT 131 
#define  T_FMT_AMPM 130 
 TYPE_14__* XLOCALE_CTYPE (TYPE_2__*) ; 
#define  YESEXPR 129 
#define  YESSTR 128 
 size_t _REL (int const) ; 
 TYPE_12__* __get_current_messages_locale (TYPE_2__*) ; 
 TYPE_10__* __get_current_monetary_locale (TYPE_2__*) ; 
 TYPE_8__* __get_current_numeric_locale (TYPE_2__*) ; 
 TYPE_6__* __get_current_time_locale (TYPE_2__*) ; 
 TYPE_4__* localeconv_l (TYPE_2__*) ; 
 char* reallocf (char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

char *
nl_langinfo_l(nl_item item, locale_t loc)
{
   char *ret, *cs;
   const char *s;
   FIX_LOCALE(loc);

   switch (item) {
	case CODESET:
		s = XLOCALE_CTYPE(loc)->runes->__encoding;
		if (strcmp(s, "EUC-CN") == 0)
			ret = "eucCN";
		else if (strcmp(s, "EUC-JP") == 0)
			ret = "eucJP";
		else if (strcmp(s, "EUC-KR") == 0)
			ret = "eucKR";
		else if (strcmp(s, "EUC-TW") == 0)
			ret = "eucTW";
		else if (strcmp(s, "BIG5") == 0)
			ret = "Big5";
		else if (strcmp(s, "MSKanji") == 0)
			ret = "SJIS";
		else if (strcmp(s, "NONE") == 0)
			ret = "US-ASCII";
		else if (strncmp(s, "NONE:", 5) == 0)
			ret = (char *)(s + 5);
		else
			ret = (char *)s;
		break;
	case D_T_FMT:
		ret = (char *) __get_current_time_locale(loc)->c_fmt;
		break;
	case D_FMT:
		ret = (char *) __get_current_time_locale(loc)->x_fmt;
		break;
	case T_FMT:
		ret = (char *) __get_current_time_locale(loc)->X_fmt;
		break;
	case T_FMT_AMPM:
		ret = (char *) __get_current_time_locale(loc)->ampm_fmt;
		break;
	case AM_STR:
		ret = (char *) __get_current_time_locale(loc)->am;
		break;
	case PM_STR:
		ret = (char *) __get_current_time_locale(loc)->pm;
		break;
	case DAY_1: case DAY_2: case DAY_3:
	case DAY_4: case DAY_5: case DAY_6: case DAY_7:
		ret = (char*) __get_current_time_locale(loc)->weekday[_REL(DAY_1)];
		break;
	case ABDAY_1: case ABDAY_2: case ABDAY_3:
	case ABDAY_4: case ABDAY_5: case ABDAY_6: case ABDAY_7:
		ret = (char*) __get_current_time_locale(loc)->wday[_REL(ABDAY_1)];
		break;
	case MON_1: case MON_2: case MON_3: case MON_4:
	case MON_5: case MON_6: case MON_7: case MON_8:
	case MON_9: case MON_10: case MON_11: case MON_12:
		ret = (char*) __get_current_time_locale(loc)->month[_REL(MON_1)];
		break;
	case ABMON_1: case ABMON_2: case ABMON_3: case ABMON_4:
	case ABMON_5: case ABMON_6: case ABMON_7: case ABMON_8:
	case ABMON_9: case ABMON_10: case ABMON_11: case ABMON_12:
		ret = (char*) __get_current_time_locale(loc)->mon[_REL(ABMON_1)];
		break;
	case ALTMON_1: case ALTMON_2: case ALTMON_3: case ALTMON_4:
	case ALTMON_5: case ALTMON_6: case ALTMON_7: case ALTMON_8:
	case ALTMON_9: case ALTMON_10: case ALTMON_11: case ALTMON_12:
		ret = (char*)
		    __get_current_time_locale(loc)->alt_month[_REL(ALTMON_1)];
		break;
	case ERA:
		/* XXX: need to be implemented  */
		ret = "";
		break;
	case ERA_D_FMT:
		/* XXX: need to be implemented  */
		ret = "";
		break;
	case ERA_D_T_FMT:
		/* XXX: need to be implemented  */
		ret = "";
		break;
	case ERA_T_FMT:
		/* XXX: need to be implemented  */
		ret = "";
		break;
	case ALT_DIGITS:
		/* XXX: need to be implemented  */
		ret = "";
		break;
	case RADIXCHAR:
		ret = (char*) __get_current_numeric_locale(loc)->decimal_point;
		break;
	case THOUSEP:
		ret = (char*) __get_current_numeric_locale(loc)->thousands_sep;
		break;
	case YESEXPR:
		ret = (char*) __get_current_messages_locale(loc)->yesexpr;
		break;
	case NOEXPR:
		ret = (char*) __get_current_messages_locale(loc)->noexpr;
		break;
	/*
	 * YESSTR and NOSTR items marked with LEGACY are available, but not
	 * recommended by SUSv2 to be used in portable applications since
	 * they're subject to remove in future specification editions.
	 */
	case YESSTR:            /* LEGACY  */
		ret = (char*) __get_current_messages_locale(loc)->yesstr;
		break;
	case NOSTR:             /* LEGACY  */
		ret = (char*) __get_current_messages_locale(loc)->nostr;
		break;
	/*
	 * SUSv2 special formatted currency string 
	 */
	case CRNCYSTR:
		ret = "";
		cs = (char*) __get_current_monetary_locale(loc)->currency_symbol;
		if (*cs != '\0') {
			char pos = localeconv_l(loc)->p_cs_precedes;

			if (pos == localeconv_l(loc)->n_cs_precedes) {
				char psn = '\0';

				if (pos == CHAR_MAX) {
					if (strcmp(cs, __get_current_monetary_locale(loc)->mon_decimal_point) == 0)
						psn = '.';
				} else
					psn = pos ? '-' : '+';
				if (psn != '\0') {
					int clen = strlen(cs);

					if ((loc->csym = reallocf(loc->csym, clen + 2)) != NULL) {
						*loc->csym = psn;
						strcpy(loc->csym + 1, cs);
						ret = loc->csym;
					}
				}
			}
		}
		break;
	case D_MD_ORDER:        /* FreeBSD local extension */
		ret = (char *) __get_current_time_locale(loc)->md_order;
		break;
	default:
		ret = "";
   }
   return (ret);
}