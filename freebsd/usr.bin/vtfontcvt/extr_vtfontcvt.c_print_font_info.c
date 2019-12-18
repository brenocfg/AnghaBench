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

/* Variables and functions */
 int* glyph_count ; 
 int glyph_dupe ; 
 int glyph_total ; 
 int glyph_unique ; 
 int height ; 
 int* map_count ; 
 int* map_folded_count ; 
 int mapping_dupe ; 
 int mapping_total ; 
 int mapping_unique ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int width ; 

__attribute__((used)) static void
print_font_info(void)
{
	printf(
"Statistics:\n"
"- width:                       %6u\n"
"- height:                      %6u\n"
"- glyph_total:                 %6u\n"
"- glyph_normal:                %6u\n"
"- glyph_normal_right:          %6u\n"
"- glyph_bold:                  %6u\n"
"- glyph_bold_right:            %6u\n"
"- glyph_unique:                %6u\n"
"- glyph_dupe:                  %6u\n"
"- mapping_total:               %6u\n"
"- mapping_normal:              %6u\n"
"- mapping_normal_folded:       %6u\n"
"- mapping_normal_right:        %6u\n"
"- mapping_normal_right_folded: %6u\n"
"- mapping_bold:                %6u\n"
"- mapping_bold_folded:         %6u\n"
"- mapping_bold_right:          %6u\n"
"- mapping_bold_right_folded:   %6u\n"
"- mapping_unique:              %6u\n"
"- mapping_dupe:                %6u\n",
	    width, height,
	    glyph_total,
	    glyph_count[0],
	    glyph_count[1],
	    glyph_count[2],
	    glyph_count[3],
	    glyph_unique, glyph_dupe,
	    mapping_total,
	    map_count[0], map_folded_count[0],
	    map_count[1], map_folded_count[1],
	    map_count[2], map_folded_count[2],
	    map_count[3], map_folded_count[3],
	    mapping_unique, mapping_dupe);
}