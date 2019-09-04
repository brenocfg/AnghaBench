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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct patch {char const* old_name; char const* new_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quote_c_style (char const*,struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void say_patch_name(FILE *output, const char *fmt, struct patch *patch)
{
	struct strbuf sb = STRBUF_INIT;

	if (patch->old_name && patch->new_name &&
	    strcmp(patch->old_name, patch->new_name)) {
		quote_c_style(patch->old_name, &sb, NULL, 0);
		strbuf_addstr(&sb, " => ");
		quote_c_style(patch->new_name, &sb, NULL, 0);
	} else {
		const char *n = patch->new_name;
		if (!n)
			n = patch->old_name;
		quote_c_style(n, &sb, NULL, 0);
	}
	fprintf(output, fmt, sb.buf);
	fputc('\n', output);
	strbuf_release(&sb);
}