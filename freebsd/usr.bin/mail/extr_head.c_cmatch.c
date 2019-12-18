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

/* Variables and functions */
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 int /*<<< orphan*/  islower (unsigned char) ; 
 int /*<<< orphan*/  ispunct (unsigned char) ; 
 int /*<<< orphan*/  isupper (unsigned char) ; 

int
cmatch(char *cp, char *tp)
{

	while (*cp != '\0' && *tp != '\0')
		switch (*tp++) {
		case 'a':
			if (!islower((unsigned char)*cp++))
				return (0);
			break;
		case 'A':
			if (!isupper((unsigned char)*cp++))
				return (0);
			break;
		case ' ':
			if (*cp++ != ' ')
				return (0);
			break;
		case '0':
			if (!isdigit((unsigned char)*cp++))
				return (0);
			break;
		case 'O':
			if (*cp != ' ' && !isdigit((unsigned char)*cp))
				return (0);
			cp++;
			break;
		case 'p':
			if (!ispunct((unsigned char)*cp++))
				return (0);
			break;
		case 'P':
			if (*cp != ' ' && !ispunct((unsigned char)*cp))
				return (0);
			cp++;
			break;
		case ':':
			if (*cp++ != ':')
				return (0);
			break;
		case 'N':
			if (*cp++ != '\n')
				return (0);
			break;
		}
	if (*cp != '\0' || *tp != '\0')
		return (0);
	return (1);
}