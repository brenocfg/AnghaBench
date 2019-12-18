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
struct prompt {int dummy; } ;
struct datalink {int dummy; } ;
struct bundle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYS_ALL ; 
 int ReadSystem (struct bundle*,char const*,char const*,struct prompt*,struct datalink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSTEM_EXEC ; 
 int modeok ; 
 int /*<<< orphan*/  modereq ; 
 int userok ; 

int
system_Select(struct bundle *bundle, const char *name, const char *file,
             struct prompt *prompt, struct datalink *cx)
{
  userok = modeok = 1;
  modereq = PHYS_ALL;
  return ReadSystem(bundle, name, file, prompt, cx, SYSTEM_EXEC);
}