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
struct TYPE_2__ {scalar_t__ color_scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int COLORS ; 
 scalar_t__ MONOKAI ; 
 scalar_t__ STD_GREEN ; 
 int /*<<< orphan*/  colors256_green ; 
 int /*<<< orphan*/  colors256_mono ; 
 int /*<<< orphan*/  colors256_monokai ; 
 int /*<<< orphan*/  colors8_green ; 
 int /*<<< orphan*/  colors8_mono ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  nocolors ; 
 int /*<<< orphan*/  parse_colors (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_default_colors (void)
{
  /* no colors */
  if (COLORS < 8)
    parse_colors (nocolors, ARRAY_SIZE (nocolors));

  /* 256 colors, and no color scheme set or set to monokai */
  if (COLORS == 256 && (!conf.color_scheme || conf.color_scheme == MONOKAI))
    parse_colors (colors256_monokai, ARRAY_SIZE (colors256_monokai));
  /* otherwise use 16 colors scheme */
  else if (COLORS > 16) {
    if (conf.color_scheme == STD_GREEN)
      parse_colors (colors256_green, ARRAY_SIZE (colors256_green));
    else
      parse_colors (colors256_mono, ARRAY_SIZE (colors256_mono));
  }

  /* 8 colors */
  if (COLORS >= 8 && COLORS <= 16) {
    if (conf.color_scheme == STD_GREEN)
      parse_colors (colors8_green, ARRAY_SIZE (colors8_green));
    else
      parse_colors (colors8_mono, ARRAY_SIZE (colors8_mono));
  }
}