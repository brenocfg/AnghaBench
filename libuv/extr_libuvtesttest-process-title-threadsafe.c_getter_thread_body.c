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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * titles ; 
 scalar_t__ uv_get_process_title (char*,int) ; 
 int /*<<< orphan*/  uv_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void getter_thread_body(void* arg) {
  char buffer[512];

  for (;;) {
    ASSERT(0 == uv_get_process_title(buffer, sizeof(buffer)));
    ASSERT(
      0 == strcmp(buffer, titles[0]) ||
      0 == strcmp(buffer, titles[1]) ||
      0 == strcmp(buffer, titles[2]) ||
      0 == strcmp(buffer, titles[3]));

    uv_sleep(0);
  }
}