#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double dv; double iv; } ;
struct TYPE_5__ {TYPE_1__ value; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ucl_object_t ;
typedef  double int64_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  UCL_CHARACTER_WHITESPACE ; 
 int /*<<< orphan*/  UCL_FLOAT ; 
 int /*<<< orphan*/  UCL_INT ; 
 int /*<<< orphan*/  UCL_TIME ; 
 scalar_t__ errno ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ isxdigit (char const) ; 
 double strtod (char const*,char**) ; 
 double strtoimax (char const*,char**,int) ; 
 char tolower (char const) ; 
 scalar_t__ ucl_lex_is_atom_end (char const) ; 
 double ucl_lex_num_multiplier (char const,int) ; 
 double ucl_lex_time_multiplier (char const) ; 
 int /*<<< orphan*/  ucl_test_character (char const,int /*<<< orphan*/ ) ; 

int
ucl_maybe_parse_number (ucl_object_t *obj,
		const char *start, const char *end, const char **pos,
		bool allow_double, bool number_bytes, bool allow_time)
{
	const char *p = start, *c = start;
	char *endptr;
	bool got_dot = false, got_exp = false, need_double = false,
			is_time = false, valid_start = false, is_hex = false,
			is_neg = false;
	double dv = 0;
	int64_t lv = 0;

	if (*p == '-') {
		is_neg = true;
		c ++;
		p ++;
	}
	while (p < end) {
		if (is_hex && isxdigit (*p)) {
			p ++;
		}
		else if (isdigit (*p)) {
			valid_start = true;
			p ++;
		}
		else if (!is_hex && (*p == 'x' || *p == 'X')) {
			is_hex = true;
			allow_double = false;
			c = p + 1;
		}
		else if (allow_double) {
			if (p == c) {
				/* Empty digits sequence, not a number */
				*pos = start;
				return EINVAL;
			}
			else if (*p == '.') {
				if (got_dot) {
					/* Double dots, not a number */
					*pos = start;
					return EINVAL;
				}
				else {
					got_dot = true;
					need_double = true;
					p ++;
				}
			}
			else if (*p == 'e' || *p == 'E') {
				if (got_exp) {
					/* Double exp, not a number */
					*pos = start;
					return EINVAL;
				}
				else {
					got_exp = true;
					need_double = true;
					p ++;
					if (p >= end) {
						*pos = start;
						return EINVAL;
					}
					if (!isdigit (*p) && *p != '+' && *p != '-') {
						/* Wrong exponent sign */
						*pos = start;
						return EINVAL;
					}
					else {
						p ++;
					}
				}
			}
			else {
				/* Got the end of the number, need to check */
				break;
			}
		}
		else {
			break;
		}
	}

	if (!valid_start) {
		*pos = start;
		return EINVAL;
	}

	errno = 0;
	if (need_double) {
		dv = strtod (c, &endptr);
	}
	else {
		if (is_hex) {
			lv = strtoimax (c, &endptr, 16);
		}
		else {
			lv = strtoimax (c, &endptr, 10);
		}
	}
	if (errno == ERANGE) {
		*pos = start;
		return ERANGE;
	}

	/* Now check endptr */
	if (endptr == NULL || ucl_lex_is_atom_end (*endptr) || *endptr == '\0') {
		p = endptr;
		goto set_obj;
	}

	if (endptr < end && endptr != start) {
		p = endptr;
		switch (*p) {
		case 'm':
		case 'M':
		case 'g':
		case 'G':
		case 'k':
		case 'K':
			if (end - p >= 2) {
				if (p[1] == 's' || p[1] == 'S') {
					/* Milliseconds */
					if (!need_double) {
						need_double = true;
						dv = lv;
					}
					is_time = true;
					if (p[0] == 'm' || p[0] == 'M') {
						dv /= 1000.;
					}
					else {
						dv *= ucl_lex_num_multiplier (*p, false);
					}
					p += 2;
					goto set_obj;
				}
				else if (number_bytes || (p[1] == 'b' || p[1] == 'B')) {
					/* Bytes */
					if (need_double) {
						need_double = false;
						lv = dv;
					}
					lv *= ucl_lex_num_multiplier (*p, true);
					p += 2;
					goto set_obj;
				}
				else if (ucl_lex_is_atom_end (p[1])) {
					if (need_double) {
						dv *= ucl_lex_num_multiplier (*p, false);
					}
					else {
						lv *= ucl_lex_num_multiplier (*p, number_bytes);
					}
					p ++;
					goto set_obj;
				}
				else if (allow_time && end - p >= 3) {
					if (tolower (p[0]) == 'm' &&
							tolower (p[1]) == 'i' &&
							tolower (p[2]) == 'n') {
						/* Minutes */
						if (!need_double) {
							need_double = true;
							dv = lv;
						}
						is_time = true;
						dv *= 60.;
						p += 3;
						goto set_obj;
					}
				}
			}
			else {
				if (need_double) {
					dv *= ucl_lex_num_multiplier (*p, false);
				}
				else {
					lv *= ucl_lex_num_multiplier (*p, number_bytes);
				}
				p ++;
				goto set_obj;
			}
			break;
		case 'S':
		case 's':
			if (allow_time &&
					(p == end - 1 || ucl_lex_is_atom_end (p[1]))) {
				if (!need_double) {
					need_double = true;
					dv = lv;
				}
				p ++;
				is_time = true;
				goto set_obj;
			}
			break;
		case 'h':
		case 'H':
		case 'd':
		case 'D':
		case 'w':
		case 'W':
		case 'Y':
		case 'y':
			if (allow_time &&
					(p == end - 1 || ucl_lex_is_atom_end (p[1]))) {
				if (!need_double) {
					need_double = true;
					dv = lv;
				}
				is_time = true;
				dv *= ucl_lex_time_multiplier (*p);
				p ++;
				goto set_obj;
			}
			break;
		case '\t':
		case ' ':
			while (p < end && ucl_test_character(*p, UCL_CHARACTER_WHITESPACE)) {
				p++;
			}
			if (ucl_lex_is_atom_end(*p))
				goto set_obj;
			break;
		}
	}
	else if (endptr == end) {
		/* Just a number at the end of chunk */
		p = endptr;
		goto set_obj;
	}

	*pos = c;
	return EINVAL;

set_obj:
	if (obj != NULL) {
		if (allow_double && (need_double || is_time)) {
			if (!is_time) {
				obj->type = UCL_FLOAT;
			}
			else {
				obj->type = UCL_TIME;
			}
			obj->value.dv = is_neg ? (-dv) : dv;
		}
		else {
			obj->type = UCL_INT;
			obj->value.iv = is_neg ? (-lv) : lv;
		}
	}
	*pos = p;
	return 0;
}