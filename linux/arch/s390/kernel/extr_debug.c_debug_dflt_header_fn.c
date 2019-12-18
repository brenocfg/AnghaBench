#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct debug_view {int dummy; } ;
typedef  int /*<<< orphan*/  debug_info_t ;
struct TYPE_5__ {unsigned int level; int /*<<< orphan*/  cpuid; scalar_t__ exception; } ;
struct TYPE_6__ {int stck; TYPE_1__ fields; } ;
struct TYPE_7__ {TYPE_2__ id; scalar_t__ caller; } ;
typedef  TYPE_3__ debug_entry_t ;

/* Variables and functions */
 int TOD_UNIX_EPOCH ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 unsigned long do_div (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ sprintf (char*,char*,int,unsigned long,unsigned long,unsigned int,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * tod_clock_base ; 

int debug_dflt_header_fn(debug_info_t *id, struct debug_view *view,
			 int area, debug_entry_t *entry, char *out_buf)
{
	unsigned long base, sec, usec;
	unsigned long caller;
	unsigned int level;
	char *except_str;
	int rc = 0;

	level = entry->id.fields.level;
	base = (*(unsigned long *) &tod_clock_base[0]) >> 4;
	sec = (entry->id.stck >> 12) + base - (TOD_UNIX_EPOCH >> 12);
	usec = do_div(sec, USEC_PER_SEC);

	if (entry->id.fields.exception)
		except_str = "*";
	else
		except_str = "-";
	caller = (unsigned long) entry->caller;
	rc += sprintf(out_buf, "%02i %011ld:%06lu %1u %1s %02i %pK  ",
		      area, sec, usec, level, except_str,
		      entry->id.fields.cpuid, (void *)caller);
	return rc;
}