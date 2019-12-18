#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum tui_status { ____Placeholder_tui_status } tui_status ;
typedef  enum tui_register_display_type { ____Placeholder_tui_register_display_type } tui_register_display_type ;
typedef  enum tui_layout_type { ____Placeholder_tui_layout_type } tui_layout_type ;
struct TYPE_4__ {scalar_t__ regs_display_type; } ;
struct TYPE_5__ {TYPE_1__ data_display_info; } ;
struct TYPE_6__ {TYPE_2__ detail; } ;

/* Variables and functions */
 int DISASSEM_COMMAND ; 
 int DISASSEM_DATA_COMMAND ; 
 int SRC_COMMAND ; 
 int SRC_DATA_COMMAND ; 
 int SRC_DISASSEM_COMMAND ; 
 TYPE_3__* TUI_DATA_WIN ; 
 scalar_t__ TUI_DFLOAT_REGS ; 
 int TUI_FAILURE ; 
 char* TUI_FLOAT_REGS_NAME ; 
 int TUI_GENERAL_AND_SPECIAL_REGS ; 
 int TUI_GENERAL_REGS ; 
 char* TUI_GENERAL_REGS_NAME ; 
 char* TUI_GENERAL_SPECIAL_REGS_NAME ; 
 scalar_t__ TUI_SFLOAT_REGS ; 
 int TUI_SPECIAL_REGS ; 
 char* TUI_SPECIAL_REGS_NAME ; 
 int TUI_SUCCESS ; 
 scalar_t__ TUI_UNDEFINED_REGS ; 
 int UNDEFINED_LAYOUT ; 
 int next_layout () ; 
 int prev_layout () ; 
 int strlen (char const*) ; 
 scalar_t__ subset_compare (char*,char*) ; 
 char toupper (char) ; 
 int tui_current_layout () ; 
 int /*<<< orphan*/  tui_set_layout (int,int) ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xstrdup (char const*) ; 

enum tui_status
tui_set_layout_for_display_command (const char *layout_name)
{
  enum tui_status status = TUI_SUCCESS;

  if (layout_name != (char *) NULL)
    {
      int i;
      char *buf_ptr;
      enum tui_layout_type new_layout = UNDEFINED_LAYOUT;
      enum tui_register_display_type dpy_type = TUI_UNDEFINED_REGS;
      enum tui_layout_type cur_layout = tui_current_layout ();

      buf_ptr = (char *) xstrdup (layout_name);
      for (i = 0; (i < strlen (layout_name)); i++)
	buf_ptr[i] = toupper (buf_ptr[i]);

      /* First check for ambiguous input */
      if (strlen (buf_ptr) <= 1 && (*buf_ptr == 'S' || *buf_ptr == '$'))
	{
	  warning ("Ambiguous command input.\n");
	  status = TUI_FAILURE;
	}
      else
	{
	  if (subset_compare (buf_ptr, "SRC"))
	    new_layout = SRC_COMMAND;
	  else if (subset_compare (buf_ptr, "ASM"))
	    new_layout = DISASSEM_COMMAND;
	  else if (subset_compare (buf_ptr, "SPLIT"))
	    new_layout = SRC_DISASSEM_COMMAND;
	  else if (subset_compare (buf_ptr, "REGS") ||
		   subset_compare (buf_ptr, TUI_GENERAL_SPECIAL_REGS_NAME) ||
		   subset_compare (buf_ptr, TUI_GENERAL_REGS_NAME) ||
		   subset_compare (buf_ptr, TUI_FLOAT_REGS_NAME) ||
		   subset_compare (buf_ptr, TUI_SPECIAL_REGS_NAME))
	    {
	      if (cur_layout == SRC_COMMAND || cur_layout == SRC_DATA_COMMAND)
		new_layout = SRC_DATA_COMMAND;
	      else
		new_layout = DISASSEM_DATA_COMMAND;

/* could ifdef out the following code. when compile with -z, there are null 
   pointer references that cause a core dump if 'layout regs' is the first 
   layout command issued by the user. HP has asked us to hook up this code 
   - edie epstein
 */
	      if (subset_compare (buf_ptr, TUI_FLOAT_REGS_NAME))
		{
		  if (TUI_DATA_WIN->detail.data_display_info.regs_display_type !=
		      TUI_SFLOAT_REGS &&
		      TUI_DATA_WIN->detail.data_display_info.regs_display_type !=
		      TUI_DFLOAT_REGS)
		    dpy_type = TUI_SFLOAT_REGS;
		  else
		    dpy_type =
		      TUI_DATA_WIN->detail.data_display_info.regs_display_type;
		}
	      else if (subset_compare (buf_ptr,
				      TUI_GENERAL_SPECIAL_REGS_NAME))
		dpy_type = TUI_GENERAL_AND_SPECIAL_REGS;
	      else if (subset_compare (buf_ptr, TUI_GENERAL_REGS_NAME))
		dpy_type = TUI_GENERAL_REGS;
	      else if (subset_compare (buf_ptr, TUI_SPECIAL_REGS_NAME))
		dpy_type = TUI_SPECIAL_REGS;
	      else if (TUI_DATA_WIN)
		{
		  if (TUI_DATA_WIN->detail.data_display_info.regs_display_type !=
		      TUI_UNDEFINED_REGS)
		    dpy_type =
		      TUI_DATA_WIN->detail.data_display_info.regs_display_type;
		  else
		    dpy_type = TUI_GENERAL_REGS;
		}

/* end of potential ifdef 
 */

/* if ifdefed out code above, then assume that the user wishes to display the 
   general purpose registers 
 */

/*              dpy_type = TUI_GENERAL_REGS; 
 */
	    }
	  else if (subset_compare (buf_ptr, "NEXT"))
	    new_layout = next_layout ();
	  else if (subset_compare (buf_ptr, "PREV"))
	    new_layout = prev_layout ();
	  else
	    status = TUI_FAILURE;
	  xfree (buf_ptr);

	  tui_set_layout (new_layout, dpy_type);
	}
    }
  else
    status = TUI_FAILURE;

  return status;
}