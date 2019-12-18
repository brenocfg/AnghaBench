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
typedef  char const* uint16_t ;
struct buf_pr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bprintf (struct buf_pr*,char*,char const*) ; 
 int /*<<< orphan*/  icmpcodes ; 
 char* match_value (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
print_reject_code(struct buf_pr *bp, uint16_t code)
{
	char const *s;

	if ((s = match_value(icmpcodes, code)) != NULL)
		bprintf(bp, "unreach %s", s);
	else
		bprintf(bp, "unreach %u", code);
}