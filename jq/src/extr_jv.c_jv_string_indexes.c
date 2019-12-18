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
 char* _jq_memmem (char const*,int,char const*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_array () ; 
 int /*<<< orphan*/  jv_array_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_number (int) ; 
 int jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 

jv jv_string_indexes(jv j, jv k) {
  assert(JVP_HAS_KIND(j, JV_KIND_STRING));
  assert(JVP_HAS_KIND(k, JV_KIND_STRING));
  const char *jstr = jv_string_value(j);
  const char *idxstr = jv_string_value(k);
  const char *p;
  int jlen = jv_string_length_bytes(jv_copy(j));
  int idxlen = jv_string_length_bytes(jv_copy(k));
  jv a = jv_array();

  if (idxlen != 0) {
    p = jstr;
    while ((p = _jq_memmem(p, (jstr + jlen) - p, idxstr, idxlen)) != NULL) {
      a = jv_array_append(a, jv_number(p - jstr));
      p += idxlen;
    }
  }
  jv_free(j);
  jv_free(k);
  return a;
}