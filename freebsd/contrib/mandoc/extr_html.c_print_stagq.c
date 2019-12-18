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
typedef  struct tag {scalar_t__ tag; struct tag const* next; } const tag ;
struct html {struct tag const* tag; } ;

/* Variables and functions */
 scalar_t__ TAG_P ; 
 scalar_t__ TAG_PRE ; 
 int /*<<< orphan*/  print_ctag (struct html*,struct tag const*) ; 

void
print_stagq(struct html *h, const struct tag *suntil)
{
	struct tag	*this, *next;

	for (this = h->tag; this != NULL; this = next) {
		next = this->next;
		if (this == suntil || (next == suntil &&
		    (this->tag == TAG_P || this->tag == TAG_PRE)))
			break;
		print_ctag(h, this);
	}
}