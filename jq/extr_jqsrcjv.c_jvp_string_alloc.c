#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int count; } ;
struct TYPE_6__ {scalar_t__ alloc_length; TYPE_1__ refcnt; } ;
typedef  TYPE_2__ jvp_string ;

/* Variables and functions */
 TYPE_2__* jv_mem_alloc (scalar_t__) ; 

__attribute__((used)) static jvp_string* jvp_string_alloc(uint32_t size) {
  jvp_string* s = jv_mem_alloc(sizeof(jvp_string) + size + 1);
  s->refcnt.count = 1;
  s->alloc_length = size;
  return s;
}