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
typedef  int /*<<< orphan*/  dl_t ;
typedef  int /*<<< orphan*/  dl_status ;

/* Variables and functions */
 int /*<<< orphan*/  DL_SUCCESS ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 

dl_status my_on_detach(dl_t dl, const char *device_id, int device_num) {
  printf("on_detach %s %d\n", device_id, device_num);
  return DL_SUCCESS;
}