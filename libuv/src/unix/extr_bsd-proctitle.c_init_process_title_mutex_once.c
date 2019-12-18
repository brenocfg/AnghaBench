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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  process_title_mutex ; 
 scalar_t__ uv_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_process_title_mutex_once(void) {
  if (uv_mutex_init(&process_title_mutex))
    abort();
}