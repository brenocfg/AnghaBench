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
struct ui_out_level {int type; scalar_t__ field_count; } ;
struct ui_out {scalar_t__ level; } ;
typedef  enum ui_out_type { ____Placeholder_ui_out_type } ui_out_type ;

/* Variables and functions */
 scalar_t__ MAX_UI_OUT_LEVELS ; 
 struct ui_out_level* current_level (struct ui_out*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

__attribute__((used)) static int
push_level (struct ui_out *uiout,
	    enum ui_out_type type,
	    const char *id)
{
  struct ui_out_level *current;
  /* We had better not overflow the buffer. */
  uiout->level++;
  gdb_assert (uiout->level >= 0 && uiout->level < MAX_UI_OUT_LEVELS);
  current = current_level (uiout);
  current->field_count = 0;
  current->type = type;
  return uiout->level;
}