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
 int /*<<< orphan*/  printf (char*,int,size_t) ; 
 size_t xPortGetFreeHeapSize () ; 

__attribute__((used)) static void show_free_mem(int idx) {
  size_t res = xPortGetFreeHeapSize();
  printf("dbg free memory(%d): %d\r\n", idx, res);
}