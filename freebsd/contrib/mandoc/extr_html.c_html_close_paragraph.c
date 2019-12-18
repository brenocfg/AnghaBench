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
struct tag {scalar_t__ closed; int tag; struct tag* next; } ;
struct html {struct tag* tag; } ;

/* Variables and functions */
#define  TAG_A 130 
#define  TAG_P 129 
#define  TAG_PRE 128 
 int /*<<< orphan*/  print_tagq (struct html*,struct tag*) ; 

void
html_close_paragraph(struct html *h)
{
	struct tag	*t;

	for (t = h->tag; t != NULL && t->closed == 0; t = t->next) {
		switch(t->tag) {
		case TAG_P:
		case TAG_PRE:
			print_tagq(h, t);
			break;
		case TAG_A:
			print_tagq(h, t);
			continue;
		default:
			continue;
		}
		break;
	}
}