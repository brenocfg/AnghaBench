#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct type {int dummy; } ;
struct field_info {TYPE_1__* fnlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  fn_fieldlist; struct TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TYPE_FN_FIELDLISTS (struct type*) ; 
 int TYPE_NFN_FIELDS (struct type*) ; 

__attribute__((used)) static int
attach_fn_fields_to_type (struct field_info *fip, struct type *type)
{
  int n;

  for (n = TYPE_NFN_FIELDS (type);
       fip->fnlist != NULL;
       fip->fnlist = fip->fnlist->next)
    {
      --n;			/* Circumvent Sun3 compiler bug */
      TYPE_FN_FIELDLISTS (type)[n] = fip->fnlist->fn_fieldlist;
    }
  return 1;
}