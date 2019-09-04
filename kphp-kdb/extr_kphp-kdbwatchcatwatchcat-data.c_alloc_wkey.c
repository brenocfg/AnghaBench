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
struct TYPE_6__ {struct TYPE_6__* l; } ;
typedef  TYPE_1__ wkey ;

/* Variables and functions */
 TYPE_1__* dl_malloc (int) ; 
 int /*<<< orphan*/  keys_cnt ; 
 int keys_memory ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* wkey_mem ; 

wkey *alloc_wkey (void) {
  keys_cnt++;

  wkey *res;
  if (wkey_mem != NULL) {
    res = wkey_mem;
    wkey_mem = wkey_mem->l;
  } else {
    keys_memory += sizeof (wkey);
    res = dl_malloc (sizeof (wkey));
  }
  memset (res, 0, sizeof (wkey));
  return res;
}