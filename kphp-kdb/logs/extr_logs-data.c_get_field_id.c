#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int field_i; TYPE_1__* fields; } ;
typedef  TYPE_2__ type_desc ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int FN ; 
 scalar_t__* std_t ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int get_field_id (type_desc *t, char *s) {
  int i;
  for (i = -FN; i < t->field_i; i += 1 + (i < 0 && std_t[i + FN])) {
    if (!strcmp (t->fields[i].name, s)) {
      return i;
    }
  }

  return -FN - 1;
}