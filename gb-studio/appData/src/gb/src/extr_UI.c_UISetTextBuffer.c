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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  UIDrawFrame (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ text_count ; 
 int /*<<< orphan*/  text_drawn ; 
 int /*<<< orphan*/  text_lines ; 
 scalar_t__ text_tile_count ; 
 scalar_t__ text_x ; 
 scalar_t__ text_y ; 

void UISetTextBuffer(unsigned char *text)
{
  UIDrawFrame(0, 2, 20, 4);
  text_drawn = FALSE;
  strcpy(text_lines, text);
  text_x = 0;
  text_y = 0;
  text_count = 0;
  text_tile_count = 0;
}