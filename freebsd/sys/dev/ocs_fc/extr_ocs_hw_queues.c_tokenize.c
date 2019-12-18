#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_7__ {char* string; int /*<<< orphan*/  subtype; void* type; } ;
typedef  TYPE_1__ tok_t ;
typedef  int int32_t ;
struct TYPE_8__ {char const* s; int /*<<< orphan*/  subtype; void* type; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 int TOKEN_LEN ; 
 void* TOK_NUMBER ; 
 void* TOK_NUMBER_LIST ; 
 void* TOK_NUMBER_VALUE ; 
 TYPE_3__* cmatches ; 
 scalar_t__ idchar (char const) ; 
 scalar_t__ idstart (char const) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ocs_isdigit (char const) ; 
 scalar_t__ ocs_isspace (char const) ; 
 scalar_t__ ocs_isxdigit (char const) ; 
 TYPE_3__* smatches ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static const char *
tokenize(const char *s, tok_t *tok)
{
	uint32_t i;

	memset(tok, 0, sizeof(*tok));

	/* Skip over whitespace */
	while (*s && ocs_isspace(*s)) {
		s++;
	}

	/* Return if nothing left in this string */
	if (*s == 0) {
		return NULL;
	}

	/* Look for single character matches */
	for (i = 0; i < ARRAY_SIZE(cmatches); i++) {
		if (cmatches[i].s[0] == *s) {
			tok->type = cmatches[i].type;
			tok->subtype = cmatches[i].subtype;
			tok->string[0] = *s++;
			return s;
		}
	}

	/* Scan for a hex number or decimal */
	if ((s[0] == '0') && ((s[1] == 'x') || (s[1] == 'X'))) {
		char *p = tok->string;

		tok->type = TOK_NUMBER;

		*p++ = *s++;
		*p++ = *s++;
		while ((*s == '.') || ocs_isxdigit(*s)) {
			if ((p - tok->string) < (int32_t)sizeof(tok->string)) {
				*p++ = *s;
			}
			if (*s == ',') {
				tok->type = TOK_NUMBER_LIST;
			}
			s++;
		}
		*p = 0;
		return s;
	} else if (ocs_isdigit(*s)) {
		char *p = tok->string;

		tok->type = TOK_NUMBER;
		while ((*s == ',') || ocs_isdigit(*s)) {
			if ((p - tok->string) < (int32_t)sizeof(tok->string)) {
				*p++ = *s;
			}
			if (*s == ',') {
				tok->type = TOK_NUMBER_LIST;
			}
			s++;
		}
		*p = 0;
		return s;
	}

	/* Scan for an ID */
	if (idstart(*s)) {
		char *p = tok->string;

		for (*p++ = *s++; idchar(*s); s++) {
			if ((p - tok->string) < TOKEN_LEN) {
				*p++ = *s;
			}
		}

		/* See if this is a $ number value */
		if (tok->string[0] == '$') {
			tok->type = TOK_NUMBER_VALUE;
		} else {
			/* Look for a string match */
			for (i = 0; i < ARRAY_SIZE(smatches); i++) {
				if (strcmp(smatches[i].s, tok->string) == 0) {
					tok->type = smatches[i].type;
					tok->subtype = smatches[i].subtype;
					return s;
				}
			}
		}
	}
	return s;
}