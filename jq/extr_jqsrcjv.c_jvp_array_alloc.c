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
struct TYPE_5__ {int count; } ;
struct TYPE_6__ {unsigned int alloc_length; scalar_t__ length; TYPE_1__ refcnt; } ;
typedef  TYPE_2__ jvp_array ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 TYPE_2__* jv_mem_alloc (int) ; 

__attribute__((used)) static jvp_array* jvp_array_alloc(unsigned size) {
  jvp_array* a = jv_mem_alloc(sizeof(jvp_array) + sizeof(jv) * size);
  a->refcnt.count = 1;
  a->length = 0;
  a->alloc_length = size;
  return a;
}