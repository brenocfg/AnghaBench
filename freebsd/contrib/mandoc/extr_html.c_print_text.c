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
struct html {int flags; int /*<<< orphan*/ * metaf; scalar_t__ col; } ;

/* Variables and functions */
 int HTML_IGNDELIM ; 
 int HTML_KEEP ; 
 int HTML_NONEWLINE ; 
 int HTML_NONOSPACE ; 
 int HTML_NOSPACE ; 
 int HTML_PREKEEP ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_encode (struct html*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_endword (struct html*) ; 
 int /*<<< orphan*/  print_indent (struct html*) ; 
 int /*<<< orphan*/  print_metaf (struct html*) ; 
 int /*<<< orphan*/  print_tagq (struct html*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_word (struct html*,char*) ; 

void
print_text(struct html *h, const char *word)
{
	if (h->col && (h->flags & HTML_NOSPACE) == 0) {
		if ( ! (HTML_KEEP & h->flags)) {
			if (HTML_PREKEEP & h->flags)
				h->flags |= HTML_KEEP;
			print_endword(h);
		} else
			print_word(h, "&#x00A0;");
	}

	assert(h->metaf == NULL);
	print_metaf(h);
	print_indent(h);
	if ( ! print_encode(h, word, NULL, 0)) {
		if ( ! (h->flags & HTML_NONOSPACE))
			h->flags &= ~HTML_NOSPACE;
		h->flags &= ~HTML_NONEWLINE;
	} else
		h->flags |= HTML_NOSPACE | HTML_NONEWLINE;

	if (h->metaf != NULL) {
		print_tagq(h, h->metaf);
		h->metaf = NULL;
	}

	h->flags &= ~HTML_IGNDELIM;
}