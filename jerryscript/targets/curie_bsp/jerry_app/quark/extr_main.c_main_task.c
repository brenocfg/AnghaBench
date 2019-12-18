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
typedef  int /*<<< orphan*/  OS_ERR_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  E_OS_OK ; 
 int /*<<< orphan*/  WDT_MAX_TIMEOUT_MS ; 
 int /*<<< orphan*/  bsp_init () ; 
 int /*<<< orphan*/  cfw_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_start () ; 
 int /*<<< orphan*/  queue ; 
 int /*<<< orphan*/  queue_process_message_wait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_keepalive () ; 
 int /*<<< orphan*/  wdt_start (int /*<<< orphan*/ ) ; 

void main_task (void *param)
{
  /* Init BSP (also init BSP on ARC core) */
  queue = bsp_init ();
  /* start Quark watchdog */
  wdt_start (WDT_MAX_TIMEOUT_MS);
  /* Init the CFW */
  cfw_init (queue);
  jerry_start ();
  /* Loop to process message queue */
  while (1)
  {
    OS_ERR_TYPE err = E_OS_OK;
    /* Process message with a given timeout */
    queue_process_message_wait (queue, 5000, &err);
    /* Acknowledge the system watchdog to prevent panic and reset */
    wdt_keepalive ();
  }
}