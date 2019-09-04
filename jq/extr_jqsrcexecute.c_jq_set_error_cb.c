#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* err_cb_data; int /*<<< orphan*/ * err_cb; } ;
typedef  TYPE_1__ jq_state ;
typedef  int /*<<< orphan*/ * jq_msg_cb ;

/* Variables and functions */
 int /*<<< orphan*/ * default_err_cb ; 
 void* stderr ; 

void jq_set_error_cb(jq_state *jq, jq_msg_cb cb, void *data) {
  if (cb == NULL) {
    jq->err_cb = default_err_cb;
    jq->err_cb_data = stderr;
  } else {
    jq->err_cb = cb;
    jq->err_cb_data = data;
  }
}