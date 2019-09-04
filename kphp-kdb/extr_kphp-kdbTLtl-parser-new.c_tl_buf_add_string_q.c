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
 int /*<<< orphan*/  tl_buf_add_string (char*,int) ; 
 int /*<<< orphan*/  tl_buf_add_string_nospace (char*,int) ; 

void tl_buf_add_string_q (char *s, int len, int x) {
  if (x) {
    tl_buf_add_string (s, len);
  } else {
    tl_buf_add_string_nospace (s, len);
  }
}