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
 int sprintf (char*,char*,char*) ; 

int friends_generate_new_key (char *buff, char *key, int len, void *E) {
	if (*key != '%') {
	  return sprintf (buff, "%%%s", key);
	} else {
	  return sprintf (buff, "%s", key);
	}
}