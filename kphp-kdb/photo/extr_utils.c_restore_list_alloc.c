#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int val; } ;
typedef  TYPE_1__ restore_list ;

/* Variables and functions */
 TYPE_1__* dl_malloc (int) ; 
 int /*<<< orphan*/  restore_list_connect (TYPE_1__*,TYPE_1__*) ; 

restore_list *restore_list_alloc (int val) {
  restore_list *res = dl_malloc (sizeof (restore_list));
  restore_list_connect (res, res);
  res->val = val;
  return res;
}