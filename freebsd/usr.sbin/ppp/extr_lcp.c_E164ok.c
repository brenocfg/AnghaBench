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
struct callback {int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int
E164ok(struct callback *cb, char *req, int sz)
{
  char list[sizeof cb->msg], *next;
  int len;

  if (!strcmp(cb->msg, "*"))
    return 1;

  strncpy(list, cb->msg, sizeof list - 1);
  list[sizeof list - 1] = '\0';
  for (next = strtok(list, ","); next; next = strtok(NULL, ",")) {
    len = strlen(next);
    if (sz == len && !memcmp(list, req, sz))
      return 1;
  }
  return 0;
}