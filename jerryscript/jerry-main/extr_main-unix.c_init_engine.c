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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  jerry_init_flag_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_debugger_after_connect (int) ; 
 scalar_t__ jerryx_debugger_rp_create () ; 
 int jerryx_debugger_serial_create (char*) ; 
 int jerryx_debugger_tcp_create (int /*<<< orphan*/ ) ; 
 scalar_t__ jerryx_debugger_ws_create () ; 
 int /*<<< orphan*/  jerryx_handler_assert ; 
 int /*<<< orphan*/  jerryx_handler_gc ; 
 int /*<<< orphan*/  jerryx_handler_print ; 
 int /*<<< orphan*/  jerryx_handler_resource_name ; 
 int /*<<< orphan*/  register_js_function (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
init_engine (jerry_init_flag_t flags, /**< initialized flags for the engine */
             char *debug_channel, /**< enable the debugger init or not */
             char *debug_protocol, /**< enable the debugger init or not */
             uint16_t debug_port, /**< the debugger port for tcp protocol */
             char *debug_serial_config) /**< configuration string for serial protocol */
{
  jerry_init (flags);
  if (strcmp (debug_channel, ""))
  {
    bool protocol = false;

    if (!strcmp (debug_protocol, "tcp"))
    {
      protocol = jerryx_debugger_tcp_create (debug_port);
    }
    else
    {
      assert (!strcmp (debug_protocol, "serial"));
      protocol = jerryx_debugger_serial_create (debug_serial_config);
    }

    if (!strcmp (debug_channel, "rawpacket"))
    {
      jerryx_debugger_after_connect (protocol && jerryx_debugger_rp_create ());
    }
    else
    {
      assert (!strcmp (debug_channel, "websocket"));
      jerryx_debugger_after_connect (protocol && jerryx_debugger_ws_create ());
    }
  }

  register_js_function ("assert", jerryx_handler_assert);
  register_js_function ("gc", jerryx_handler_gc);
  register_js_function ("print", jerryx_handler_print);
  register_js_function ("resourceName", jerryx_handler_resource_name);
}