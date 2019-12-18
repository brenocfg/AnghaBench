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
struct tui_gen_win_info {int type; } ;

/* Variables and functions */
 char* CMD_NAME ; 
#define  CMD_WIN 131 
 char* DATA_NAME ; 
#define  DATA_WIN 130 
 char* DISASSEM_NAME ; 
#define  DISASSEM_WIN 129 
 char* SRC_NAME ; 
#define  SRC_WIN 128 

char *
tui_win_name (struct tui_gen_win_info * win_info)
{
  char *name = (char *) NULL;

  switch (win_info->type)
    {
    case SRC_WIN:
      name = SRC_NAME;
      break;
    case CMD_WIN:
      name = CMD_NAME;
      break;
    case DISASSEM_WIN:
      name = DISASSEM_NAME;
      break;
    case DATA_WIN:
      name = DATA_NAME;
      break;
    default:
      name = "";
      break;
    }

  return name;
}