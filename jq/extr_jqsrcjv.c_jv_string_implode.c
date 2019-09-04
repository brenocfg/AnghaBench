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
 scalar_t__ JV_KIND_ARRAY ; 
 scalar_t__ JV_KIND_NUMBER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jv_array_get (int /*<<< orphan*/ ,int) ; 
 int jv_array_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int jv_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_append_codepoint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jv_string_empty (int) ; 

jv jv_string_implode(jv j) {
  assert(jv_get_kind(j) == JV_KIND_ARRAY);
  int len = jv_array_length(jv_copy(j));
  jv s = jv_string_empty(len);
  int i;

  assert(len >= 0);

  for (i = 0; i < len; i++) {
    jv n = jv_array_get(jv_copy(j), i);
    assert(jv_get_kind(n) == JV_KIND_NUMBER);
    int nv = jv_number_value(n);
    if (nv > 0x10FFFF)
      nv = 0xFFFD; // U+FFFD REPLACEMENT CHARACTER
    s = jv_string_append_codepoint(s, nv);
  }

  jv_free(j);
  return s;
}