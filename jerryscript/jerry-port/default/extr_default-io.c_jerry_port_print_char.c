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
typedef  int /*<<< orphan*/  jerry_size_t ;
typedef  int /*<<< orphan*/  jerry_char_t ;

/* Variables and functions */
 scalar_t__ DEBUG_BUFFER_SIZE ; 
 char* debug_buffer ; 
 scalar_t__ debug_buffer_index ; 
 int /*<<< orphan*/  jerry_debugger_send_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 

void
jerry_port_print_char (char c) /**< the character to print */
{
  putchar (c);

#if defined (JERRY_DEBUGGER) && (JERRY_DEBUGGER == 1)
  debug_buffer[debug_buffer_index++] = c;

  if ((debug_buffer_index == DEBUG_BUFFER_SIZE) || (c == '\n'))
  {
    jerry_debugger_send_output ((jerry_char_t *) debug_buffer, (jerry_size_t) debug_buffer_index);
    debug_buffer_index = 0;
  }
#endif /* defined (JERRY_DEBUGGER) && (JERRY_DEBUGGER == 1) */
}