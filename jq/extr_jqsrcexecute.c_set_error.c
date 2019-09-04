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
typedef  int /*<<< orphan*/  jv ;
struct TYPE_3__ {int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ jq_state ;

/* Variables and functions */
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_error(jq_state *jq, jv value) {
  // Record so try/catch can find it.
  jv_free(jq->error);
  jq->error = value;
}