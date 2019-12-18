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
struct object_slot {int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_NULL ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 struct object_slot* jvp_object_get_slot (int /*<<< orphan*/ ,int) ; 
 int jvp_object_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jvp_object_length(jv object) {
  int n = 0;
  for (int i=0; i<jvp_object_size(object); i++) {
    struct object_slot* slot = jvp_object_get_slot(object, i);
    if (jv_get_kind(slot->string) != JV_KIND_NULL) n++;
  }
  return n;
}