#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* min; int passphrase_words; } ;
typedef  TYPE_1__ passwdqc_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  expected_different (int,int) ; 
 scalar_t__ isalpha (int) ; 
 scalar_t__ isascii (int) ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ islower (int) ; 
 scalar_t__ isupper (int) ; 
 int /*<<< orphan*/  strchr (char const*,int) ; 

__attribute__((used)) static int is_simple(passwdqc_params_t *params, const char *newpass)
{
	int length, classes, words, chars;
	int digits, lowers, uppers, others, unknowns;
	int c, p;

	length = classes = words = chars = 0;
	digits = lowers = uppers = others = unknowns = 0;
	p = ' ';
	while ((c = (unsigned char)newpass[length])) {
		length++;

		if (!isascii(c)) unknowns++; else
		if (isdigit(c)) digits++; else
		if (islower(c)) lowers++; else
		if (isupper(c)) uppers++; else
			others++;

		if (isascii(c) && isalpha(c) && isascii(p) && !isalpha(p))
			words++;
		p = c;

		if (!strchr(&newpass[length], c))
			chars++;
	}

	if (!length) return 1;

/* Upper case characters and digits used in common ways don't increase the
 * strength of a password */
	c = (unsigned char)newpass[0];
	if (uppers && isascii(c) && isupper(c)) uppers--;
	c = (unsigned char)newpass[length - 1];
	if (digits && isascii(c) && isdigit(c)) digits--;

/* Count the number of different character classes we've seen. We assume
 * that there're no non-ASCII characters for digits. */
	classes = 0;
	if (digits) classes++;
	if (lowers) classes++;
	if (uppers) classes++;
	if (others) classes++;
	if (unknowns && (!classes || (digits && classes == 1))) classes++;

	for (; classes > 0; classes--)
	switch (classes) {
	case 1:
		if (length >= params->min[0] &&
		    chars >= expected_different(10, params->min[0]) - 1)
			return 0;
		return 1;

	case 2:
		if (length >= params->min[1] &&
		    chars >= expected_different(36, params->min[1]) - 1)
			return 0;
		if (!params->passphrase_words ||
		    words < params->passphrase_words)
			continue;
		if (length >= params->min[2] &&
		    chars >= expected_different(27, params->min[2]) - 1)
			return 0;
		continue;

	case 3:
		if (length >= params->min[3] &&
		    chars >= expected_different(62, params->min[3]) - 1)
			return 0;
		continue;

	case 4:
		if (length >= params->min[4] &&
		    chars >= expected_different(95, params->min[4]) - 1)
			return 0;
		continue;
	}

	return 1;
}