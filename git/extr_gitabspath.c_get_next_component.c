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
struct strbuf {char* buf; } ;

/* Variables and functions */
 scalar_t__ is_dir_sep (char) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void get_next_component(struct strbuf *next, struct strbuf *remaining)
{
	char *start = NULL;
	char *end = NULL;

	strbuf_reset(next);

	/* look for the next component */
	/* Skip sequences of multiple path-separators */
	for (start = remaining->buf; is_dir_sep(*start); start++)
		; /* nothing */
	/* Find end of the path component */
	for (end = start; *end && !is_dir_sep(*end); end++)
		; /* nothing */

	strbuf_add(next, start, end - start);
	/* remove the component from 'remaining' */
	strbuf_remove(remaining, 0, end - remaining->buf);
}