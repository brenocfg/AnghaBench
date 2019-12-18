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
struct packet {struct option_data* options; } ;
struct option_data {unsigned char* data; size_t len; } ;

/* Variables and functions */
 size_t DHO_DOMAIN_SEARCH ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expand_search_domain_name (struct option_data*,size_t*,unsigned char**) ; 
 int find_search_domain_name_len (struct option_data*,size_t*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 

void
expand_domain_search(struct packet *packet)
{
	size_t offset;
	int expanded_len, next_domain_len;
	struct option_data *option;
	unsigned char *domain_search, *cursor;

	if (packet->options[DHO_DOMAIN_SEARCH].data == NULL)
		return;

	option = &packet->options[DHO_DOMAIN_SEARCH];

	/* Compute final expanded length. */
	expanded_len = 0;
	offset = 0;
	while (offset < option->len) {
		next_domain_len = find_search_domain_name_len(option, &offset);
		if (next_domain_len < 0)
			/* The Domain Search option value is invalid. */
			return;

		/* We add 1 for the space between domain names. */
		expanded_len += next_domain_len + 1;
	}
	if (expanded_len > 0)
		/* Remove 1 for the superfluous trailing space. */
		--expanded_len;

	domain_search = malloc(expanded_len + 1);
	if (domain_search == NULL)
		error("Can't allocate storage for expanded domain-search\n");

	offset = 0;
	cursor = domain_search;
	while (offset < option->len) {
		expand_search_domain_name(option, &offset, &cursor);
		cursor[0] = ' ';
		cursor++;
	}
	domain_search[expanded_len] = '\0';

	free(option->data);
	option->len = expanded_len;
	option->data = domain_search;
}