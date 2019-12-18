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
 scalar_t__ JV_KIND_NULL ; 
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int jv_array_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_number (int) ; 
 double jv_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_object_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int jv_string_length_codepoints (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_slice(jv j, jv slice, int* pstart, int* pend) {
  // Array slices
  jv start_jv = jv_object_get(jv_copy(slice), jv_string("start"));
  jv end_jv = jv_object_get(slice, jv_string("end"));
  if (jv_get_kind(start_jv) == JV_KIND_NULL) {
    jv_free(start_jv);
    start_jv = jv_number(0);
  }
  int len;
  if (jv_get_kind(j) == JV_KIND_ARRAY) {
    len = jv_array_length(j);
  } else if (jv_get_kind(j) == JV_KIND_STRING) {
    len = jv_string_length_codepoints(j);
  } else {
    jv_free(j);
    return 0;
  }
  if (jv_get_kind(end_jv) == JV_KIND_NULL) {
    jv_free(end_jv);
    end_jv = jv_number(len);
  }
  if (jv_get_kind(start_jv) != JV_KIND_NUMBER ||
      jv_get_kind(end_jv) != JV_KIND_NUMBER) {
    jv_free(start_jv);
    jv_free(end_jv);
    return 0;
  } else {
    double dstart = jv_number_value(start_jv);
    double dend = jv_number_value(end_jv);
    jv_free(start_jv);
    jv_free(end_jv);
    if (dstart < 0) dstart += len;
    if (dend < 0) dend += len;
    if (dstart < 0) dstart = 0;
    if (dstart > len) dstart = len;

    int start = (int)dstart;
    int end = (dend > len) ? len : (int)dend;
    // Ends are exclusive but e.g. 1 < 1.5 so :1.5 should be :2 not :1
    if(end < dend) end += 1;

    if (end > len) end = len;
    if (end < start) end = start;
    assert(0 <= start && start <= end && end <= len);
    *pstart = start;
    *pend = end;
    return 1;
  }
}