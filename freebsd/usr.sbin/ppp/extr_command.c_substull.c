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
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long long) ; 
 char* subst (char*,char const*,char*) ; 

__attribute__((used)) static char *
substull(char *tgt, const char *oldstr, unsigned long long ull)
{
  char buf[21];

  snprintf(buf, sizeof buf, "%llu", ull);

  return subst(tgt, oldstr, buf);
}