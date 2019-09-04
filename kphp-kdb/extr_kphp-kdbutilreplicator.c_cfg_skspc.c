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
 char* cfg_cur ; 

__attribute__((used)) static int cfg_skspc (void) {
  while (*cfg_cur == ' ' || *cfg_cur == 9 || *cfg_cur == 10 || *cfg_cur == 13) {
    cfg_cur++;
  }
  return (unsigned char) *cfg_cur;
}