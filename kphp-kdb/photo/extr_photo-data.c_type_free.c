#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int field_i; int field_n; TYPE_3__* fields; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ type_desc ;
typedef  int /*<<< orphan*/  field_desc ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dl_strfree (int /*<<< orphan*/ ) ; 

void type_free (type_desc *t) {
  dl_strfree (t->name);
  int j;
  for (j = 0; j < t->field_i; j++) {
    dl_strfree (t->fields[j].name);
  }
  dl_free (t->fields, sizeof (field_desc) * t->field_n);
}