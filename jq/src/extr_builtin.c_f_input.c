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
typedef  int /*<<< orphan*/  (* jq_input_cb ) (int /*<<< orphan*/ *,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  jq_get_input_cb (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,void*),void**) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_invalid_has_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 

__attribute__((used)) static jv f_input(jq_state *jq, jv input) {
  jv_free(input);
  jq_input_cb cb;
  void *data;
  jq_get_input_cb(jq, &cb, &data);
  if (cb == NULL)
    return jv_invalid_with_msg(jv_string("break"));
  jv v = cb(jq, data);
  if (jv_is_valid(v) || jv_invalid_has_msg(jv_copy(v)))
    return v;
  return jv_invalid_with_msg(jv_string("break"));
}