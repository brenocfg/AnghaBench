#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  attrs; scalar_t__ bc; } ;
typedef  TYPE_1__ jq_state ;

/* Variables and functions */
 int /*<<< orphan*/  bytecode_free (scalar_t__) ; 
 int /*<<< orphan*/  jq_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_mem_free (TYPE_1__*) ; 

void jq_teardown(jq_state **jq) {
  jq_state *old_jq = *jq;
  if (old_jq == NULL)
    return;
  *jq = NULL;

  jq_reset(old_jq);
  bytecode_free(old_jq->bc);
  old_jq->bc = 0;
  jv_free(old_jq->attrs);

  jv_mem_free(old_jq);
}