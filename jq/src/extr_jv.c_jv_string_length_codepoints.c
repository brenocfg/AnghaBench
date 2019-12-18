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
 int /*<<< orphan*/  JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 
 char* jvp_utf8_next (char const*,char const*,int*) ; 

int jv_string_length_codepoints(jv j) {
  assert(JVP_HAS_KIND(j, JV_KIND_STRING));
  const char* i = jv_string_value(j);
  const char* end = i + jv_string_length_bytes(jv_copy(j));
  int c = 0, len = 0;
  while ((i = jvp_utf8_next(i, end, &c))) len++;
  jv_free(j);
  return len;
}