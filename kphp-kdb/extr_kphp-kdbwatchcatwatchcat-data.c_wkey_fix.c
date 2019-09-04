#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * next_time; } ;
typedef  TYPE_1__ wkey ;

/* Variables and functions */
 int /*<<< orphan*/  add_entry_time (TYPE_1__*,int) ; 
 int /*<<< orphan*/  del_entry_time (TYPE_1__*) ; 

inline void wkey_fix (wkey *k, int timeout) {
  if (k->next_time != NULL) {
    del_entry_time (k);
  }
  add_entry_time (k, timeout);
}