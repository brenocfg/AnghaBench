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
typedef  int /*<<< orphan*/  netbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int read_in (int /*<<< orphan*/ *,char*,int) ; 

inline void st_safe_read_in (netbuffer_t *H, char *__data, int len) {
  assert (read_in (H, __data, len) == len);
  int i;
  for (i = 0; i < len; i++) {
    if (__data[i] == 0) {
      __data[i] = ' ';
    }
  }
  __data[len] = 0;
}