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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int max_frm_size; } ;

/* Variables and functions */
 scalar_t__ FD_SETSIZE ; 
 int /*<<< orphan*/  LOG (char*) ; 
 scalar_t__ WS_OPCODE_BIN ; 
 scalar_t__ WS_OPCODE_TEXT ; 
 TYPE_1__ wsconfig ; 

__attribute__((used)) static int
validate_fifo_packet (uint32_t listener, uint32_t type, int size)
{
  if (listener > FD_SETSIZE) {
    LOG (("Invalid listener\n"));
    return 1;
  }

  if (type != WS_OPCODE_TEXT && type != WS_OPCODE_BIN) {
    LOG (("Invalid fifo packet type\n"));
    return 1;
  }

  if (size > wsconfig.max_frm_size) {
    LOG (("Invalid fifo packet size\n"));
    return 1;
  }

  return 0;
}