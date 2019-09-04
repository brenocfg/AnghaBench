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
 char* buff ; 
 int /*<<< orphan*/  flush_buff () ; 
 char* result_buff ; 
 scalar_t__ result_buff_len ; 

char *finish_buff () {
  if (result_buff_len) {
    flush_buff ();
    return result_buff;
  } else {
    return buff;
  }
}