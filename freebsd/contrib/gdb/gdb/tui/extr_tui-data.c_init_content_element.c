#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* file_name; char* proc_name; int /*<<< orphan*/  addr; int /*<<< orphan*/  line_no; } ;
struct TYPE_11__ {char* name; char* content; void* highlight; int /*<<< orphan*/ * value; int /*<<< orphan*/  item_no; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {char* line; } ;
struct TYPE_14__ {int type; } ;
struct TYPE_8__ {int /*<<< orphan*/  line_no; } ;
struct TYPE_9__ {char* line; void* has_break; void* is_exec_point; TYPE_1__ line_or_addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  simple_string; TYPE_5__ locator; TYPE_4__ data; TYPE_3__ command; TYPE_7__ data_window; TYPE_2__ source; } ;
struct tui_win_element {TYPE_6__ which_element; void* highlight; } ;
struct tui_gen_win_info {void** content; int content_size; } ;
typedef  enum tui_win_type { ____Placeholder_tui_win_type } tui_win_type ;

/* Variables and functions */
#define  CMD_WIN 134 
#define  DATA_ITEM_WIN 133 
#define  DATA_WIN 132 
#define  DISASSEM_WIN 131 
#define  EXEC_INFO_WIN 130 
 void* FALSE ; 
#define  LOCATOR_WIN 129 
#define  SRC_WIN 128 
 int /*<<< orphan*/  TUI_REGISTER ; 
 int /*<<< orphan*/  UNDEFINED_ITEM ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 
 scalar_t__ tui_alloc_content (int,int) ; 
 int /*<<< orphan*/  tui_init_generic_part (TYPE_7__*) ; 

void
init_content_element (struct tui_win_element * element, enum tui_win_type type)
{
  element->highlight = FALSE;
  switch (type)
    {
    case SRC_WIN:
    case DISASSEM_WIN:
      element->which_element.source.line = (char *) NULL;
      element->which_element.source.line_or_addr.line_no = 0;
      element->which_element.source.is_exec_point = FALSE;
      element->which_element.source.has_break = FALSE;
      break;
    case DATA_WIN:
      tui_init_generic_part (&element->which_element.data_window);
      element->which_element.data_window.type = DATA_ITEM_WIN;
      ((struct tui_gen_win_info *) & element->which_element.data_window)->content =
	(void **) tui_alloc_content (1, DATA_ITEM_WIN);
      ((struct tui_gen_win_info *)
       & element->which_element.data_window)->content_size = 1;
      break;
    case CMD_WIN:
      element->which_element.command.line = (char *) NULL;
      break;
    case DATA_ITEM_WIN:
      element->which_element.data.name = (char *) NULL;
      element->which_element.data.type = TUI_REGISTER;
      element->which_element.data.item_no = UNDEFINED_ITEM;
      element->which_element.data.value = NULL;
      element->which_element.data.highlight = FALSE;
      element->which_element.data.content = (char*) NULL;
      break;
    case LOCATOR_WIN:
      element->which_element.locator.file_name[0] =
	element->which_element.locator.proc_name[0] = (char) 0;
      element->which_element.locator.line_no = 0;
      element->which_element.locator.addr = 0;
      break;
    case EXEC_INFO_WIN:
      memset(element->which_element.simple_string, ' ',
             sizeof(element->which_element.simple_string));
      break;
    default:
      break;
    }
}