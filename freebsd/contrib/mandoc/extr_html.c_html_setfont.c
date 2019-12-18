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
struct html {int metal; int metac; } ;
typedef  enum mandoc_esc { ____Placeholder_mandoc_esc } mandoc_esc ;

/* Variables and functions */
#define  ESCAPE_FONT 134 
#define  ESCAPE_FONTBI 133 
#define  ESCAPE_FONTBOLD 132 
#define  ESCAPE_FONTCW 131 
#define  ESCAPE_FONTITALIC 130 
#define  ESCAPE_FONTPREV 129 
#define  ESCAPE_FONTROMAN 128 

int
html_setfont(struct html *h, enum mandoc_esc font)
{
	switch (font) {
	case ESCAPE_FONTPREV:
		font = h->metal;
		break;
	case ESCAPE_FONTITALIC:
	case ESCAPE_FONTBOLD:
	case ESCAPE_FONTBI:
	case ESCAPE_FONTCW:
	case ESCAPE_FONTROMAN:
		break;
	case ESCAPE_FONT:
		font = ESCAPE_FONTROMAN;
		break;
	default:
		return 0;
	}
	h->metal = h->metac;
	h->metac = font;
	return 1;
}