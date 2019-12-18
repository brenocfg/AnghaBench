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
struct exception_event_record {int dummy; } ;
struct TYPE_2__ {struct exception_event_record* (* to_get_current_exception_event ) () ;} ;

/* Variables and functions */
 TYPE_1__ debug_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 struct exception_event_record* stub1 () ; 

__attribute__((used)) static struct exception_event_record *
debug_to_get_current_exception_event (void)
{
  struct exception_event_record *result;
  result = debug_target.to_get_current_exception_event ();
  fprintf_unfiltered (gdb_stdlog, "target get_current_exception_event ()\n");
  return result;
}