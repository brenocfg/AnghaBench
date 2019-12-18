#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ jvp_string ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ jvp_string_length (TYPE_1__*) ; 
 TYPE_1__* jvp_string_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int jvp_string_equal(jv a, jv b) {
  assert(JVP_HAS_KIND(a, JV_KIND_STRING));
  assert(JVP_HAS_KIND(b, JV_KIND_STRING));
  jvp_string* stra = jvp_string_ptr(a);
  jvp_string* strb = jvp_string_ptr(b);
  if (jvp_string_length(stra) != jvp_string_length(strb)) return 0;
  return memcmp(stra->data, strb->data, jvp_string_length(stra)) == 0;
}