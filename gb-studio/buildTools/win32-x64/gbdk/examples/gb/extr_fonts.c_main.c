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
typedef  int /*<<< orphan*/  font_t ;

/* Variables and functions */
 int /*<<< orphan*/  DKGREY ; 
 int M_NO_SCROLL ; 
 int /*<<< orphan*/  SOLID ; 
 int /*<<< orphan*/  WHITE ; 
 int /*<<< orphan*/  color (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  font_ibm ; 
 int /*<<< orphan*/  font_init () ; 
 int /*<<< orphan*/  font_italic ; 
 int /*<<< orphan*/  font_load (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  font_min ; 
 int /*<<< orphan*/  font_set (int /*<<< orphan*/ ) ; 
 int get_mode () ; 
 int /*<<< orphan*/  mode (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void main(void)
{
    font_t ibm_font, italic_font, min_font;
    int i;

    /* First, init the font system */
    font_init();

    /* Load all the fonts that we can */
    ibm_font = font_load(font_ibm);  /* 96 tiles */
    italic_font = font_load(font_italic);   /* 93 tiles */
    
    /* Load this one with dk grey background and white foreground */
    color(WHITE, DKGREY, SOLID);
    
    min_font = font_load(font_min);

    /* Turn scrolling off (why not?) */
    mode(get_mode() | M_NO_SCROLL);

    /* Print some text! */
    
    /* IBM font */
    font_set(ibm_font);
    printf("Font demo.\n\n");

    printf("IBM Font #!?123\n");

    /* In italic */
    font_set(italic_font);
    for (i=1; i!=5; i++) {
	printf("In italics, line %u\n", i);
    }

    /* With a minimal, colour changed font */
    font_set(min_font);
    printf("Minimal 36 tile font\n");

    /* Done */
    font_set(ibm_font);
    printf("\nDone!");
}