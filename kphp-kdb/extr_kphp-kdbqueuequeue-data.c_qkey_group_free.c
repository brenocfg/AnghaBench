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
struct TYPE_4__ {int n; struct TYPE_4__* k; struct TYPE_4__* r; } ;
typedef  TYPE_1__ qkey_group ;
typedef  int /*<<< orphan*/  qkey ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (TYPE_1__*,int) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  keys_memory ; 

void qkey_group_free (qkey_group *k) {
  keys_memory -= dl_get_memory_used();
  dl_free (k->r, sizeof (char) * k->n);
  dl_free (k->k, sizeof (qkey *) * k->n);
  dl_free (k, sizeof (qkey_group));
  keys_memory += dl_get_memory_used();
}