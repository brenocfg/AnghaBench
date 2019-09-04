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
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 TYPE_1__* CMD ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static char *client_command_generator (const char *text, int state) {
  static int len;
  static int idx;
  if (!state) {
    idx = 0;
    len = strlen (text);
    if (!strncmp ("(", text, len)) {
      return strdup ("(");
    }
  }
  while (1) {
    const char *name = CMD[idx++].name;
    if (name == NULL) {
      break;
    }
    if (!strncmp (name, text, len)) {
      return strdup (name);
    }
  }
  return NULL;
}