#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsmntok_t ;
typedef  scalar_t__ jsmnerr_t ;
struct TYPE_4__ {int toknext; } ;
typedef  TYPE_1__ jsmn_parser ;

/* Variables and functions */
 scalar_t__ JSMN_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsmn_init (TYPE_1__*) ; 
 scalar_t__ jsmn_parse (TYPE_1__*,char*,size_t,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  jsmn_strerror (scalar_t__) ; 
 int /*<<< orphan*/ * malloc (unsigned int) ; 
 char* mapfile (char const*,size_t*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmapfile (char*,size_t) ; 

jsmntok_t *parse_json(const char *fn, char **map, size_t *size, int *len)
{
	jsmn_parser parser;
	jsmntok_t *tokens;
	jsmnerr_t res;
	unsigned sz;

	*map = mapfile(fn, size);
	if (!*map)
		return NULL;
	/* Heuristic */
	sz = *size * 16;
	tokens = malloc(sz);
	if (!tokens)
		goto error;
	jsmn_init(&parser);
	res = jsmn_parse(&parser, *map, *size, tokens,
			 sz / sizeof(jsmntok_t));
	if (res != JSMN_SUCCESS) {
		pr_err("%s: json error %s\n", fn, jsmn_strerror(res));
		goto error_free;
	}
	if (len)
		*len = parser.toknext;
	return tokens;
error_free:
	free(tokens);
error:
	unmapfile(*map, *size);
	return NULL;
}