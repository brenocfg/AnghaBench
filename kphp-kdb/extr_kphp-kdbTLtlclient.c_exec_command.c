#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* f ) (char*) ;scalar_t__ name; } ;

/* Variables and functions */
 TYPE_1__* CMD ; 
 scalar_t__ isspace (char) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (scalar_t__,char*,int) ; 
 int stub1 (char*) ; 

int exec_command (char *input) {
  char *p = strchr (input, ' ');
  if (p == NULL) {
    p = input + strlen (input);
  }
  int l = p - input;
  while (*p && isspace (*p)) {
    p++;
  }
  int k;
  for (k = 0; CMD[k].name; k++) {
    if (!strncmp (CMD[k].name, input, l)) {
      return CMD[k].f (p);
    }
  }
  return -1;
}