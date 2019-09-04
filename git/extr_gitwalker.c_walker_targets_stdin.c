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
 scalar_t__ EOF ; 
 int /*<<< orphan*/  REALLOC_ARRAY (char const**,int) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char*,char) ; 
 char* xstrdup (char*) ; 
 char* xstrdup_or_null (char*) ; 

int walker_targets_stdin(char ***target, const char ***write_ref)
{
	int targets = 0, targets_alloc = 0;
	struct strbuf buf = STRBUF_INIT;
	*target = NULL; *write_ref = NULL;
	while (1) {
		char *rf_one = NULL;
		char *tg_one;

		if (strbuf_getline_lf(&buf, stdin) == EOF)
			break;
		tg_one = buf.buf;
		rf_one = strchr(tg_one, '\t');
		if (rf_one)
			*rf_one++ = 0;

		if (targets >= targets_alloc) {
			targets_alloc = targets_alloc ? targets_alloc * 2 : 64;
			REALLOC_ARRAY(*target, targets_alloc);
			REALLOC_ARRAY(*write_ref, targets_alloc);
		}
		(*target)[targets] = xstrdup(tg_one);
		(*write_ref)[targets] = xstrdup_or_null(rf_one);
		targets++;
	}
	strbuf_release(&buf);
	return targets;
}