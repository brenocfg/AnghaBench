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
struct strbuf_expand_dict_entry {scalar_t__ value; scalar_t__ placeholder; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,scalar_t__) ; 
 size_t strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char const*,scalar_t__,size_t) ; 

size_t strbuf_expand_dict_cb(struct strbuf *sb, const char *placeholder,
		void *context)
{
	struct strbuf_expand_dict_entry *e = context;
	size_t len;

	for (; e->placeholder && (len = strlen(e->placeholder)); e++) {
		if (!strncmp(placeholder, e->placeholder, len)) {
			if (e->value)
				strbuf_addstr(sb, e->value);
			return len;
		}
	}
	return 0;
}