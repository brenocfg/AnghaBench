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
typedef  struct tag {struct tag const* next; } const tag ;
struct html {struct tag const* tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_ctag (struct html*,struct tag const*) ; 

void
print_tagq(struct html *h, const struct tag *until)
{
	struct tag	*this, *next;

	for (this = h->tag; this != NULL; this = next) {
		next = this == until ? NULL : this->next;
		print_ctag(h, this);
	}
}