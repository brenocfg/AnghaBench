#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int* map_int_int_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  volumes ; 

int get_server (int vid) {
  int *t = map_int_int_get (&volumes, vid);
  if (t != NULL) {
    return *t;
  }
  return vid / 1000;
}