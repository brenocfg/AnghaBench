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
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  jv_string_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_string_append (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  jvp_string_copy_replace_bad (char const*,int) ; 
 scalar_t__ jvp_utf8_is_valid (char const*,char const*) ; 

jv jv_string_append_buf(jv a, const char* buf, int len) {
  if (jvp_utf8_is_valid(buf, buf+len)) {
    a = jvp_string_append(a, buf, len);
  } else {
    jv b = jvp_string_copy_replace_bad(buf, len);
    a = jv_string_concat(a, b);
  }
  return a;
}