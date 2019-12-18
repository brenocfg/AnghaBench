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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ BPNO_LETTER_NUM ; 
 scalar_t__ ISBLANK (char) ; 
 scalar_t__ ISCNTRL (char) ; 
 int /*<<< orphan*/  ISDIGIT (char) ; 
 int /*<<< orphan*/  STRTOUL (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int32_t
parse_breakpoint_no(char* args)
{
  char* ps = args;
  uint32_t l;

  if ((*ps == '0')||(strlen(ps) >= BPNO_LETTER_NUM)) {
    return 0;
  }

  while (!(ISBLANK(*ps)||ISCNTRL(*ps))) {
    if (!ISDIGIT(*ps)) {
      return 0;
    }
    ps++;
  }

  STRTOUL(l, args);
  return l;
}