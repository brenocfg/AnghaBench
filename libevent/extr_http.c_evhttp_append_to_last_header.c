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
struct evkeyvalq {int dummy; } ;
struct evkeyval {char* value; } ;

/* Variables and functions */
 struct evkeyval* TAILQ_LAST (struct evkeyvalq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evkeyvalq ; 
 int /*<<< orphan*/  evutil_rtrim_lws_ (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* mm_realloc (char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
evhttp_append_to_last_header(struct evkeyvalq *headers, char *line)
{
	struct evkeyval *header = TAILQ_LAST(headers, evkeyvalq);
	char *newval;
	size_t old_len, line_len;

	if (header == NULL)
		return (-1);

	old_len = strlen(header->value);

	/* Strip space from start and end of line. */
	while (*line == ' ' || *line == '\t')
		++line;
	evutil_rtrim_lws_(line);

	line_len = strlen(line);

	newval = mm_realloc(header->value, old_len + line_len + 2);
	if (newval == NULL)
		return (-1);

	newval[old_len] = ' ';
	memcpy(newval + old_len + 1, line, line_len + 1);
	header->value = newval;

	return (0);
}