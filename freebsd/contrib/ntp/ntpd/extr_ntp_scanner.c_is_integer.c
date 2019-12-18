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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ INT_MAX ; 
 int TRUE ; 
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,scalar_t__*) ; 

__attribute__((used)) static int
is_integer(
	char *lexeme
	)
{
	int	i;
	int	is_neg;
	u_int	u_val;
	
	i = 0;

	/* Allow a leading minus sign */
	if (lexeme[i] == '-') {
		i++;
		is_neg = TRUE;
	} else {
		is_neg = FALSE;
	}

	/* Check that all the remaining characters are digits */
	for (; lexeme[i] != '\0'; i++) {
		if (!isdigit((u_char)lexeme[i]))
			return FALSE;
	}

	if (is_neg)
		return TRUE;

	/* Reject numbers that fit in unsigned but not in signed int */
	if (1 == sscanf(lexeme, "%u", &u_val))
		return (u_val <= INT_MAX);
	else
		return FALSE;
}