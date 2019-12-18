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
struct html {int metac; int /*<<< orphan*/ * metaf; } ;

/* Variables and functions */
#define  ESCAPE_FONTBI 131 
#define  ESCAPE_FONTBOLD 130 
#define  ESCAPE_FONTCW 129 
#define  ESCAPE_FONTITALIC 128 
 int /*<<< orphan*/  TAG_B ; 
 int /*<<< orphan*/  TAG_I ; 
 int /*<<< orphan*/  TAG_SPAN ; 
 void* print_otag (struct html*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_tagq (struct html*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_metaf(struct html *h)
{
	if (h->metaf) {
		print_tagq(h, h->metaf);
		h->metaf = NULL;
	}
	switch (h->metac) {
	case ESCAPE_FONTITALIC:
		h->metaf = print_otag(h, TAG_I, "");
		break;
	case ESCAPE_FONTBOLD:
		h->metaf = print_otag(h, TAG_B, "");
		break;
	case ESCAPE_FONTBI:
		h->metaf = print_otag(h, TAG_B, "");
		print_otag(h, TAG_I, "");
		break;
	case ESCAPE_FONTCW:
		h->metaf = print_otag(h, TAG_SPAN, "c", "Li");
		break;
	default:
		break;
	}
}