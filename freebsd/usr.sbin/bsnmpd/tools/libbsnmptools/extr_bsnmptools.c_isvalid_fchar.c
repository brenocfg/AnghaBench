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
typedef  char u_int ;

/* Variables and functions */
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/  isascii (char) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  isprint (char) ; 
 int /*<<< orphan*/  warnx (char*,char) ; 

__attribute__((used)) static char
isvalid_fchar(char c, int pos)
{
	if (isalpha(c)|| c == '/'|| c == '_' || c == '.' || c == '~' ||
	    (pos != 0 && isdigit(c))){
		return (c);
	}

	if (c == '\0')
		return (0);

	if (!isascii(c) || !isprint(c))
		warnx("Unexpected character %#2x", (u_int) c);
	else
		warnx("Illegal character '%c'", c);

	return (-1);
}