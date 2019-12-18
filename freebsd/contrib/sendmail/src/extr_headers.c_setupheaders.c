#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hdrinfo {int /*<<< orphan*/  hi_flags; int /*<<< orphan*/ * hi_field; } ;
struct TYPE_4__ {int /*<<< orphan*/ * hi_ruleset; int /*<<< orphan*/  hi_flags; } ;
struct TYPE_5__ {TYPE_1__ s_header; } ;
typedef  TYPE_2__ STAB ;

/* Variables and functions */
 struct hdrinfo* HdrInfo ; 
 int /*<<< orphan*/  ST_ENTER ; 
 int /*<<< orphan*/  ST_HEADER ; 
 TYPE_2__* stab (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
setupheaders()
{
	struct hdrinfo *hi;
	STAB *s;

	for (hi = HdrInfo; hi->hi_field != NULL; hi++)
	{
		s = stab(hi->hi_field, ST_HEADER, ST_ENTER);
		s->s_header.hi_flags = hi->hi_flags;
		s->s_header.hi_ruleset = NULL;
	}
}