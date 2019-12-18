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
typedef  int /*<<< orphan*/  jq_state ;

/* Variables and functions */
 scalar_t__ JV_KIND_STRING ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string_length_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static jv f_utf8bytelength(jq_state *jq, jv input) {
  if (jv_get_kind(input) != JV_KIND_STRING)
    return type_error(input, "only strings have UTF-8 byte length");
  return jv_number(jv_string_length_bytes(input));
}