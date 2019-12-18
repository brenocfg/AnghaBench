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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 char tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_double(
	char *lexeme
	)
{
	u_int num_digits = 0;  /* Number of digits read */
	u_int i;

	i = 0;

	/* Check for an optional '+' or '-' */
	if ('+' == lexeme[i] || '-' == lexeme[i])
		i++;

	/* Read the integer part */
	for (; lexeme[i] && isdigit((u_char)lexeme[i]); i++)
		num_digits++;

	/* Check for the optional decimal point */
	if ('.' == lexeme[i]) {
		i++;
		/* Check for any digits after the decimal point */
		for (; lexeme[i] && isdigit((u_char)lexeme[i]); i++)
			num_digits++;
	}

	/*
	 * The number of digits in both the decimal part and the
	 * fraction part must not be zero at this point 
	 */
	if (!num_digits)
		return 0;

	/* Check if we are done */
	if (!lexeme[i])
		return 1;

	/* There is still more input, read the exponent */
	if ('e' == tolower((u_char)lexeme[i]))
		i++;
	else
		return 0;

	/* Read an optional Sign */
	if ('+' == lexeme[i] || '-' == lexeme[i])
		i++;

	/* Now read the exponent part */
	while (lexeme[i] && isdigit((u_char)lexeme[i]))
		i++;

	/* Check if we are done */
	if (!lexeme[i])
		return 1;
	else
		return 0;
}