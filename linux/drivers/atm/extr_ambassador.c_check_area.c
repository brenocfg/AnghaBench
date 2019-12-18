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
typedef  size_t u32 ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRINTK (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 size_t virt_to_bus (void*) ; 

__attribute__((used)) static int check_area (void * start, size_t length) {
  // assumes length > 0
  const u32 fourmegmask = -1 << 22;
  const u32 twofivesixmask = -1 << 8;
  const u32 starthole = 0xE0000000;
  u32 startaddress = virt_to_bus (start);
  u32 lastaddress = startaddress+length-1;
  if ((startaddress ^ lastaddress) & fourmegmask ||
      (startaddress & twofivesixmask) == starthole) {
    PRINTK (KERN_ERR, "check_area failure: [%x,%x] - mail maintainer!",
	    startaddress, lastaddress);
    return -1;
  } else {
    return 0;
  }
}