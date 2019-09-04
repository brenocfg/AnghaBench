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
struct TYPE_4__ {int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ jvp_string ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 int /*<<< orphan*/  jv_mem_free (TYPE_1__*) ; 
 scalar_t__ jvp_refcnt_dec (int /*<<< orphan*/ *) ; 
 TYPE_1__* jvp_string_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jvp_string_free(jv js) {
  jvp_string* s = jvp_string_ptr(js);
  if (jvp_refcnt_dec(&s->refcnt)) {
    jv_mem_free(s);
  }
}