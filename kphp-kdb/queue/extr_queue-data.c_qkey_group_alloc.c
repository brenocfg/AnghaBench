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
struct TYPE_3__ {int n; int /*<<< orphan*/  r; void* k; } ;
typedef  TYPE_1__ qkey_group ;
typedef  int /*<<< orphan*/  qkey ;

/* Variables and functions */
 scalar_t__ dl_get_memory_used () ; 
 void* dl_malloc (int) ; 
 int /*<<< orphan*/  dl_malloc0 (int) ; 
 int /*<<< orphan*/  keys_memory ; 

qkey_group *qkey_group_alloc (int n) {
  keys_memory -= dl_get_memory_used();

  qkey_group *r = dl_malloc (sizeof (qkey_group));
  r->n = n;
  r->k = dl_malloc (sizeof (qkey *) * n);
  r->r = dl_malloc0 (sizeof (char) * n);

  keys_memory += dl_get_memory_used();

  return r;
}