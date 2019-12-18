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
 int JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jv_string_empty (int) ; 
 int jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_sized (char const*,int) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_clamp_slice_params (int,int*,int*) ; 
 char* jvp_utf8_next (char const*,char const*,int*) ; 

jv jv_string_slice(jv j, int start, int end) {
  assert(JVP_HAS_KIND(j, JV_KIND_STRING));
  const char *s = jv_string_value(j);
  int len = jv_string_length_bytes(jv_copy(j));
  int i;
  const char *p, *e;
  int c;
  jv res;

  jvp_clamp_slice_params(len, &start, &end);
  assert(0 <= start && start <= end && end <= len);

  /* Look for byte offset corresponding to start codepoints */
  for (p = s, i = 0; i < start; i++) {
    p = jvp_utf8_next(p, s + len, &c);
    if (p == NULL) {
      jv_free(j);
      return jv_string_empty(16);
    }
    if (c == -1) {
      jv_free(j);
      return jv_invalid_with_msg(jv_string("Invalid UTF-8 string"));
    }
  }
  /* Look for byte offset corresponding to end codepoints */
  for (e = p; e != NULL && i < end; i++) {
    e = jvp_utf8_next(e, s + len, &c);
    if (e == NULL) {
      e = s + len;
      break;
    }
    if (c == -1) {
      jv_free(j);
      return jv_invalid_with_msg(jv_string("Invalid UTF-8 string"));
    }
  }

  /*
   * NOTE: Ideally we should do here what jvp_array_slice() does instead
   * of allocating a new string as we do!  However, we assume NUL-
   * terminated strings all over, and in the jv API, so for now we waste
   * memory like a drunken navy programmer.  There's probably nothing we
   * can do about it.
   */
  res = jv_string_sized(p, e - p);
  jv_free(j);
  return res;
}