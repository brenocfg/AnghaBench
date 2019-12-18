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
struct option_data {size_t len; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int*,int) ; 

void
expand_search_domain_name(struct option_data *option, size_t *offset,
    unsigned char **domain_search)
{
	int label_len;
	size_t i, pointer;
	unsigned char *cursor;

	/*
	 * This is the same loop than the function above
	 * (find_search_domain_name_len). Therefore, we remove checks,
	 * they're already done. Here, we just make the copy.
	 */
	i = *offset;
	cursor = *domain_search;
	while (i < option->len) {
		label_len = option->data[i];
		if (label_len == 0) {
			/*
			 * A zero-length label marks the end of this
			 * domain name.
			 */
			*offset = i + 1;
			*domain_search = cursor;
			return;
		} else if (label_len & 0xC0) {
			/* This is a pointer to another list of labels. */
			pointer = ((label_len & ~(0xC0)) << 8) +
			    option->data[i + 1];

			expand_search_domain_name(option, &pointer, &cursor);

			*offset = i + 2;
			*domain_search = cursor;
			return;
		}

		/* Copy the label found. */
		memcpy(cursor, option->data + i + 1, label_len);
		cursor[label_len] = '.';

		/* Move cursor. */
		i += label_len + 1;
		cursor += label_len + 1;
	}
}