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
 int field_n ; 
 int /*<<< orphan*/ * field_name ; 
 int* field_name_len ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char const*,int) ; 

int get_field (const char *name) {
  int l = strlen (name), i;
  for (i = 0; i < field_n; i++) {
    if (field_name_len[i] == l && !strncmp (field_name[i], name, l)) {
      return i;
    }
  }
  return -1;
}