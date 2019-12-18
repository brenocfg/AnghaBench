#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct roff {TYPE_1__* man; } ;
struct buf {char* buf; int sz; } ;
typedef  enum mandoc_esc { ____Placeholder_mandoc_esc } mandoc_esc ;
struct TYPE_2__ {int /*<<< orphan*/  next; int /*<<< orphan*/ * last; } ;

/* Variables and functions */
 char ASCII_HYPH ; 
 int ESCAPE_ERROR ; 
 int ROFF_CONT ; 
 int /*<<< orphan*/  ROFF_NEXT_SIBLING ; 
 int ROFF_REPARSE ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isalpha (unsigned char) ; 
 int mandoc_asprintf (char**,char*,char*,char*) ; 
 int mandoc_escape (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int roffce_lines ; 
 int /*<<< orphan*/ * roffce_node ; 
 int roffit_lines ; 
 char* roffit_macro ; 
 size_t strcspn (char*,char*) ; 

__attribute__((used)) static int
roff_parsetext(struct roff *r, struct buf *buf, int pos, int *offs)
{
	size_t		 sz;
	const char	*start;
	char		*p;
	int		 isz;
	enum mandoc_esc	 esc;

	/* Spring the input line trap. */

	if (roffit_lines == 1) {
		isz = mandoc_asprintf(&p, "%s\n.%s", buf->buf, roffit_macro);
		free(buf->buf);
		buf->buf = p;
		buf->sz = isz + 1;
		*offs = 0;
		free(roffit_macro);
		roffit_lines = 0;
		return ROFF_REPARSE;
	} else if (roffit_lines > 1)
		--roffit_lines;

	if (roffce_node != NULL && buf->buf[pos] != '\0') {
		if (roffce_lines < 1) {
			r->man->last = roffce_node;
			r->man->next = ROFF_NEXT_SIBLING;
			roffce_lines = 0;
			roffce_node = NULL;
		} else
			roffce_lines--;
	}

	/* Convert all breakable hyphens into ASCII_HYPH. */

	start = p = buf->buf + pos;

	while (*p != '\0') {
		sz = strcspn(p, "-\\");
		p += sz;

		if (*p == '\0')
			break;

		if (*p == '\\') {
			/* Skip over escapes. */
			p++;
			esc = mandoc_escape((const char **)&p, NULL, NULL);
			if (esc == ESCAPE_ERROR)
				break;
			while (*p == '-')
				p++;
			continue;
		} else if (p == start) {
			p++;
			continue;
		}

		if (isalpha((unsigned char)p[-1]) &&
		    isalpha((unsigned char)p[1]))
			*p = ASCII_HYPH;
		p++;
	}
	return ROFF_CONT;
}