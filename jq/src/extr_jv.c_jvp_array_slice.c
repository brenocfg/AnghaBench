#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int offset; int size; } ;
typedef  TYPE_1__ jv ;

/* Variables and functions */
 int CHAR_BIT ; 
 int JVP_HAS_KIND (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_ARRAY ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ jv_array () ; 
 TYPE_1__ jv_array_append (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_array_get (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ jv_array_sized (int) ; 
 int /*<<< orphan*/  jv_copy (TYPE_1__) ; 
 int /*<<< orphan*/  jv_free (TYPE_1__) ; 
 int jvp_array_length (TYPE_1__) ; 
 int /*<<< orphan*/  jvp_clamp_slice_params (int,int*,int*) ; 

__attribute__((used)) static jv jvp_array_slice(jv a, int start, int end) {
  assert(JVP_HAS_KIND(a, JV_KIND_ARRAY));
  int len = jvp_array_length(a);
  jvp_clamp_slice_params(len, &start, &end);
  assert(0 <= start && start <= end && end <= len);

  // FIXME: maybe slice should reallocate if the slice is small enough
  if (start == end) {
    jv_free(a);
    return jv_array();
  }

  if (a.offset + start >= 1 << (sizeof(a.offset) * CHAR_BIT)) {
    jv r = jv_array_sized(end - start);
    for (int i = start; i < end; i++)
      r = jv_array_append(r, jv_array_get(jv_copy(a), i));
    jv_free(a);
    return r;
  } else {
    a.offset += start;
    a.size = end - start;
    return a;
  }
}