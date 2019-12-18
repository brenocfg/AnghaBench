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
typedef  int uint32_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int parse_ls_response(const char *response, uint32_t *mode,
					struct strbuf *dataref)
{
	const char *tab;
	const char *response_end;

	assert(response);
	response_end = response + strlen(response);

	if (*response == 'm') {	/* Missing. */
		errno = ENOENT;
		return -1;
	}

	/* Mode. */
	if (response_end - response < (signed) strlen("100644") ||
	    response[strlen("100644")] != ' ')
		die("invalid ls response: missing mode: %s", response);
	*mode = 0;
	for (; *response != ' '; response++) {
		char ch = *response;
		if (ch < '0' || ch > '7')
			die("invalid ls response: mode is not octal: %s", response);
		*mode *= 8;
		*mode += ch - '0';
	}

	/* ' blob ' or ' tree ' */
	if (response_end - response < (signed) strlen(" blob ") ||
	    (response[1] != 'b' && response[1] != 't'))
		die("unexpected ls response: not a tree or blob: %s", response);
	response += strlen(" blob ");

	/* Dataref. */
	tab = memchr(response, '\t', response_end - response);
	if (!tab)
		die("invalid ls response: missing tab: %s", response);
	strbuf_add(dataref, response, tab - response);
	return 0;
}