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
typedef  int time_t ;
struct LEXICON {char* name; size_t abbrev; int value; int type; } ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 struct LEXICON* TimeWords ; 
 scalar_t__ isalnum (unsigned char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ isupper (unsigned char) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,size_t) ; 
 int tUNUMBER ; 
 char tolower (unsigned char) ; 

__attribute__((used)) static int
nexttoken(const char **in, time_t *value)
{
	char	c;
	char	buff[64];

	for ( ; ; ) {
		while (isspace((unsigned char)**in))
			++*in;

		/* Skip parenthesized comments. */
		if (**in == '(') {
			int Count = 0;
			do {
				c = *(*in)++;
				if (c == '\0')
					return c;
				if (c == '(')
					Count++;
				else if (c == ')')
					Count--;
			} while (Count > 0);
			continue;
		}

		/* Try the next token in the word table first. */
		/* This allows us to match "2nd", for example. */
		{
			const char *src = *in;
			const struct LEXICON *tp;
			unsigned i = 0;

			/* Force to lowercase and strip '.' characters. */
			while (*src != '\0'
			    && (isalnum((unsigned char)*src) || *src == '.')
			    && i < sizeof(buff)-1) {
				if (*src != '.') {
					if (isupper((unsigned char)*src))
						buff[i++] = tolower((unsigned char)*src);
					else
						buff[i++] = *src;
				}
				src++;
			}
			buff[i] = '\0';

			/*
			 * Find the first match.  If the word can be
			 * abbreviated, make sure we match at least
			 * the minimum abbreviation.
			 */
			for (tp = TimeWords; tp->name; tp++) {
				size_t abbrev = tp->abbrev;
				if (abbrev == 0)
					abbrev = strlen(tp->name);
				if (strlen(buff) >= abbrev
				    && strncmp(tp->name, buff, strlen(buff))
				    	== 0) {
					/* Skip over token. */
					*in = src;
					/* Return the match. */
					*value = tp->value;
					return tp->type;
				}
			}
		}

		/*
		 * Not in the word table, maybe it's a number.  Note:
		 * Because '-' and '+' have other special meanings, I
		 * don't deal with signed numbers here.
		 */
		if (isdigit((unsigned char)(c = **in))) {
			for (*value = 0; isdigit((unsigned char)(c = *(*in)++)); )
				*value = 10 * *value + c - '0';
			(*in)--;
			return (tUNUMBER);
		}

		return *(*in)++;
	}
}