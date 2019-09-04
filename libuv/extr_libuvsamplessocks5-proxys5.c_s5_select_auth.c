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
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ s5_ctx ;
typedef  int s5_auth_method ;

/* Variables and functions */
 int EINVAL ; 
#define  S5_AUTH_NONE 129 
#define  S5_AUTH_PASSWD 128 
 int /*<<< orphan*/  s5_auth_pw_version ; 
 int /*<<< orphan*/  s5_req_version ; 

int s5_select_auth(s5_ctx *cx, s5_auth_method method) {
  int err;

  err = 0;
  switch (method) {
    case S5_AUTH_NONE:
      cx->state = s5_req_version;
      break;
    case S5_AUTH_PASSWD:
      cx->state = s5_auth_pw_version;
      break;
    default:
      err = -EINVAL;
  }

  return err;
}