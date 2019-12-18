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
typedef  char http_header_lex_t ;
struct TYPE_4__ {int valid; size_t count; TYPE_2__** challenges; } ;
typedef  TYPE_1__ http_auth_challenges_t ;
typedef  int /*<<< orphan*/  http_auth_challenge_t ;
struct TYPE_5__ {scalar_t__ stale; void* algo; void* opaque; void* nonce; void* qop; void* realm; int /*<<< orphan*/  scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPAS_BASIC ; 
 int /*<<< orphan*/  HTTPAS_DIGEST ; 
 int /*<<< orphan*/  HTTPAS_UNKNOWN ; 
 char HTTPHL_END ; 
 char HTTPHL_STRING ; 
 char HTTPHL_WORD ; 
 size_t MAX_CHALLENGES ; 
 int /*<<< orphan*/  fetch_syserr () ; 
 int /*<<< orphan*/  free (char*) ; 
 char http_header_lex (char const**,char*) ; 
 int /*<<< orphan*/  init_http_auth_challenge (TYPE_2__*) ; 
 void* malloc (int) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 void* strdup (char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
http_parse_authenticate(const char *cp, http_auth_challenges_t *cs)
{
	int ret = -1;
	http_header_lex_t lex;
	char *key = malloc(strlen(cp) + 1);
	char *value = malloc(strlen(cp) + 1);
	char *buf = malloc(strlen(cp) + 1);

	if (key == NULL || value == NULL || buf == NULL) {
		fetch_syserr();
		goto out;
	}

	/* In any case we've seen the header and we set the valid bit */
	cs->valid = 1;

	/* Need word first */
	lex = http_header_lex(&cp, key);
	if (lex != HTTPHL_WORD)
		goto out;

	/* Loop on challenges */
	for (; cs->count < MAX_CHALLENGES; cs->count++) {
		cs->challenges[cs->count] =
			malloc(sizeof(http_auth_challenge_t));
		if (cs->challenges[cs->count] == NULL) {
			fetch_syserr();
			goto out;
		}
		init_http_auth_challenge(cs->challenges[cs->count]);
		if (strcasecmp(key, "basic") == 0) {
			cs->challenges[cs->count]->scheme = HTTPAS_BASIC;
		} else if (strcasecmp(key, "digest") == 0) {
			cs->challenges[cs->count]->scheme = HTTPAS_DIGEST;
		} else {
			cs->challenges[cs->count]->scheme = HTTPAS_UNKNOWN;
			/*
			 * Continue parsing as basic or digest may
			 * follow, and the syntax is the same for
			 * all. We'll just ignore this one when
			 * looking at the list
			 */
		}

		/* Loop on attributes */
		for (;;) {
			/* Key */
			lex = http_header_lex(&cp, key);
			if (lex != HTTPHL_WORD)
				goto out;

			/* Equal sign */
			lex = http_header_lex(&cp, buf);
			if (lex != '=')
				goto out;

			/* Value */
			lex = http_header_lex(&cp, value);
			if (lex != HTTPHL_WORD && lex != HTTPHL_STRING)
				goto out;

			if (strcasecmp(key, "realm") == 0) {
				cs->challenges[cs->count]->realm =
				    strdup(value);
			} else if (strcasecmp(key, "qop") == 0) {
				cs->challenges[cs->count]->qop =
				    strdup(value);
			} else if (strcasecmp(key, "nonce") == 0) {
				cs->challenges[cs->count]->nonce =
				    strdup(value);
			} else if (strcasecmp(key, "opaque") == 0) {
				cs->challenges[cs->count]->opaque =
				    strdup(value);
			} else if (strcasecmp(key, "algorithm") == 0) {
				cs->challenges[cs->count]->algo =
				    strdup(value);
			} else if (strcasecmp(key, "stale") == 0) {
				cs->challenges[cs->count]->stale =
				    strcasecmp(value, "no");
			} else {
				/* ignore unknown attributes */
			}

			/* Comma or Next challenge or End */
			lex = http_header_lex(&cp, key);
			/*
			 * If we get a word here, this is the beginning of the
			 * next challenge. Break the attributes loop
			 */
			if (lex == HTTPHL_WORD)
				break;

			if (lex == HTTPHL_END) {
				/* End while looking for ',' is normal exit */
				cs->count++;
				ret = 0;
				goto out;
			}
			/* Anything else is an error */
			if (lex != ',')
				goto out;

		} /* End attributes loop */
	} /* End challenge loop */

	/*
	 * Challenges max count exceeded. This really can't happen
	 * with normal data, something's fishy -> error
	 */

out:
	if (key)
		free(key);
	if (value)
		free(value);
	if (buf)
		free(buf);
	return (ret);
}