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
typedef  int /*<<< orphan*/  (* jq_msg_cb ) (void*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  jq_get_debug_cb (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (void*,int /*<<< orphan*/ ),void**) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static jv f_debug(jq_state *jq, jv input) {
  jq_msg_cb cb;
  void *data;
  jq_get_debug_cb(jq, &cb, &data);
  if (cb != NULL)
    cb(data, jv_copy(input));
  return input;
}