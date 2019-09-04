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
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int MAX_TYPE ; 
 int /*<<< orphan*/  type_free (TYPE_1__*) ; 
 TYPE_1__* types ; 

void free_types (void) {
  int i;
  for (i = 0; i < MAX_TYPE; i++) {
    if (types[i].name != NULL) {
      type_free (&types[i]);
    }
  }
}