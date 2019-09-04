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
struct TYPE_4__ {struct TYPE_4__* l; } ;
typedef  TYPE_1__ wkey ;

/* Variables and functions */
 int /*<<< orphan*/  keys_cnt ; 
 TYPE_1__* wkey_mem ; 

void free_wkey (wkey *w) {
  keys_cnt--;

  w->l = wkey_mem;
  wkey_mem = w;
}