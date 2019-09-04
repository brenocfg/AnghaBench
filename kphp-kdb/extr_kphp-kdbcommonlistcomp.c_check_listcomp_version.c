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
 int listcomp_version ; 

int check_listcomp_version (int version) {
  if ( (version ^ listcomp_version) & 0xffff0000) {
    return 0;
  }
  if ( (version & 0xffff) > (listcomp_version & 0xffff)) {
    return 0;
  }
  return 1;
}