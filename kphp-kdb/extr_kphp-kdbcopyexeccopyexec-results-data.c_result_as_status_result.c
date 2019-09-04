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
 int /*<<< orphan*/  assert (int) ; 
 int snprintf (char*,int,char*,char*,unsigned int) ; 
 char* status_to_alpha (int) ; 

__attribute__((used)) static void result_as_status_result (char *buf, int buf_len, unsigned result) {
  int status = result >> 28;
  result &= 0x0fffffffU;
  assert (snprintf (buf, buf_len, "%s:0x%04x", status_to_alpha (status), result) < buf_len);
}