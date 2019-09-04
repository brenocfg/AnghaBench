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

/* Variables and functions */
 int /*<<< orphan*/  DEEPMIND_MAKE_SCREEN_MESSAGES ; 
 int trap_DeepmindCallback (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dmlab_make_screen_messages(int screen_width, int screen_height,
                               int line_height, int string_buffer_size) {
  return trap_DeepmindCallback(DEEPMIND_MAKE_SCREEN_MESSAGES,
                               (intptr_t)screen_width, (intptr_t)screen_height,
                               (intptr_t)line_height,
                               (intptr_t)string_buffer_size, 0, 0, 0, 0, 0, 0,
                               0, 0);
}