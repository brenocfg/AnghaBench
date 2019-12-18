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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int portTickType ;

/* Variables and functions */
 scalar_t__ jerry_task_init () ; 
 int /*<<< orphan*/  js_exit () ; 
 int /*<<< orphan*/  js_loop (int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  show_free_mem (int) ; 
 int /*<<< orphan*/  vTaskDelay (int const) ; 

__attribute__((used)) static void jerry_task(void *pvParameters) {
  if (jerry_task_init() == 0) {
    const portTickType xDelay = 100 / portTICK_RATE_MS;
    uint32_t ticknow = 0;

    for (;;) {
      vTaskDelay(xDelay);
      js_loop(ticknow);
      if (!ticknow) {
        show_free_mem(4);
      }
      ticknow++;
    }
  }
  js_exit();
}