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
struct html {int flags; scalar_t__ bufcol; scalar_t__ col; int /*<<< orphan*/  buf; scalar_t__ noindent; } ;

/* Variables and functions */
 int HTML_BUFFER ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_byte (struct html*,char) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
print_endword(struct html *h)
{
	if (h->noindent) {
		print_byte(h, ' ');
		return;
	}

	if ((h->flags & HTML_BUFFER) == 0) {
		h->col++;
		h->flags |= HTML_BUFFER;
	} else if (h->bufcol) {
		putchar(' ');
		fwrite(h->buf, h->bufcol, 1, stdout);
		h->col += h->bufcol + 1;
	}
	h->bufcol = 0;
}