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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ alloc_length; } ;
typedef  TYPE_1__ jvp_string ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ jvp_string_length (TYPE_1__*) ; 

__attribute__((used)) static uint32_t jvp_string_remaining_space(jvp_string* s) {
  assert(s->alloc_length >= jvp_string_length(s));
  uint32_t r = s->alloc_length - jvp_string_length(s);
  return r;
}