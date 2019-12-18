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
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  jvp_string_append (int /*<<< orphan*/ ,char*,int) ; 
 int jvp_utf8_encode (int /*<<< orphan*/ ,char*) ; 

jv jv_string_append_codepoint(jv a, uint32_t c) {
  char buf[5];
  int len = jvp_utf8_encode(c, buf);
  a = jvp_string_append(a, buf, len);
  return a;
}