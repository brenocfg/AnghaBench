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
 int /*<<< orphan*/  cfg_skspc () ; 

__attribute__((used)) static int cfg_getword (void) {
  cfg_skspc();
  char *s = cfg_cur;
  while ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z') || (*s >= '0' && *s <= '9') || *s == '.' || *s == '-' || *s == '_') {
    s++;
  }
  return s - cfg_cur;
}