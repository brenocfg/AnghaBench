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
struct tui_translate {scalar_t__ value; } ;
typedef  scalar_t__ chtype ;

/* Variables and functions */
 scalar_t__ ACS_HLINE ; 
 scalar_t__ ACS_LLCORNER ; 
 scalar_t__ ACS_LRCORNER ; 
 scalar_t__ ACS_ULCORNER ; 
 scalar_t__ ACS_URCORNER ; 
 scalar_t__ ACS_VLINE ; 
 struct tui_translate* translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tui_active_border_attrs ; 
 int /*<<< orphan*/  tui_active_border_mode ; 
 scalar_t__ tui_border_attrs ; 
 scalar_t__ tui_border_hline ; 
 int /*<<< orphan*/  tui_border_kind ; 
 int /*<<< orphan*/  tui_border_kind_translate_hline ; 
 int /*<<< orphan*/  tui_border_kind_translate_llcorner ; 
 int /*<<< orphan*/  tui_border_kind_translate_lrcorner ; 
 int /*<<< orphan*/  tui_border_kind_translate_ulcorner ; 
 int /*<<< orphan*/  tui_border_kind_translate_urcorner ; 
 int /*<<< orphan*/  tui_border_kind_translate_vline ; 
 scalar_t__ tui_border_llcorner ; 
 scalar_t__ tui_border_lrcorner ; 
 int /*<<< orphan*/  tui_border_mode ; 
 int /*<<< orphan*/  tui_border_mode_translate ; 
 scalar_t__ tui_border_ulcorner ; 
 scalar_t__ tui_border_urcorner ; 
 scalar_t__ tui_border_vline ; 

int
tui_update_variables (void)
{
  int need_redraw = 0;
  struct tui_translate *entry;

  entry = translate (tui_border_mode, tui_border_mode_translate);
  if (tui_border_attrs != entry->value)
    {
      tui_border_attrs = entry->value;
      need_redraw = 1;
    }
  entry = translate (tui_active_border_mode, tui_border_mode_translate);
  if (tui_active_border_attrs != entry->value)
    {
      tui_active_border_attrs = entry->value;
      need_redraw = 1;
    }

  /* If one corner changes, all characters are changed.
     Only check the first one.  The ACS characters are determined at
     run time by curses terminal management.  */
  entry = translate (tui_border_kind, tui_border_kind_translate_lrcorner);
  if (tui_border_lrcorner != (chtype) entry->value)
    {
      tui_border_lrcorner = (entry->value < 0) ? ACS_LRCORNER : entry->value;
      need_redraw = 1;
    }
  entry = translate (tui_border_kind, tui_border_kind_translate_llcorner);
  tui_border_llcorner = (entry->value < 0) ? ACS_LLCORNER : entry->value;

  entry = translate (tui_border_kind, tui_border_kind_translate_ulcorner);
  tui_border_ulcorner = (entry->value < 0) ? ACS_ULCORNER : entry->value;

  entry = translate (tui_border_kind, tui_border_kind_translate_urcorner);
  tui_border_urcorner = (entry->value < 0) ? ACS_URCORNER : entry->value;

  entry = translate (tui_border_kind, tui_border_kind_translate_hline);
  tui_border_hline = (entry->value < 0) ? ACS_HLINE : entry->value;

  entry = translate (tui_border_kind, tui_border_kind_translate_vline);
  tui_border_vline = (entry->value < 0) ? ACS_VLINE : entry->value;

  return need_redraw;
}