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
typedef  int wctype_t ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
#define  _CTYPE_A 142 
#define  _CTYPE_B 141 
#define  _CTYPE_C 140 
#define  _CTYPE_D 139 
#define  _CTYPE_G 138 
#define  _CTYPE_I 137 
#define  _CTYPE_L 136 
#define  _CTYPE_N 135 
#define  _CTYPE_P 134 
#define  _CTYPE_Q 133 
#define  _CTYPE_R 132 
#define  _CTYPE_S 131 
#define  _CTYPE_T 130 
#define  _CTYPE_U 129 
#define  _CTYPE_X 128 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

wctype_t
wctype_l(const char *property, locale_t locale)
{
	const char *propnames = 
		"alnum\0"
		"alpha\0"
		"blank\0"
		"cntrl\0"
		"digit\0"
		"graph\0"
		"lower\0"
		"print\0"
		"punct\0"
		"space\0"
		"upper\0"
		"xdigit\0"
		"ideogram\0"	/* BSD extension */
		"special\0"	/* BSD extension */
		"phonogram\0"	/* BSD extension */
		"number\0"	/* BSD extension */
		"rune\0";	/* BSD extension */
	static const wctype_t propmasks[] = {
		_CTYPE_A|_CTYPE_N,
		_CTYPE_A,
		_CTYPE_B,
		_CTYPE_C,
		_CTYPE_D,
		_CTYPE_G,
		_CTYPE_L,
		_CTYPE_R,
		_CTYPE_P,
		_CTYPE_S,
		_CTYPE_U,
		_CTYPE_X,
		_CTYPE_I,
		_CTYPE_T,
		_CTYPE_Q,
		_CTYPE_N,
		0xFFFFFF00L
	};
	size_t len1, len2;
	const char *p;
	const wctype_t *q;

	len1 = strlen(property);
	q = propmasks;
	for (p = propnames; (len2 = strlen(p)) != 0; p += len2 + 1) {
		if (len1 == len2 && memcmp(property, p, len1) == 0)
			return (*q);
		q++;
	}

	return (0UL);
}