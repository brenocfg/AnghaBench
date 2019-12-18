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
struct random_gather_extra {int bytes; } ;

/* Variables and functions */
 int sprintf (char*,char*,int) ; 

int random_generate_new_key (char *buff, char *key, int len, void *E) {
  struct random_gather_extra *extra = E;
  return sprintf (buff, "random%d", extra->bytes + 64);
}