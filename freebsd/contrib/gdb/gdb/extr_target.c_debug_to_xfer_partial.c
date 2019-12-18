#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct target_ops {int dummy; } ;
typedef  enum target_object { ____Placeholder_target_object } target_object ;
typedef  int /*<<< orphan*/  ULONGEST ;
struct TYPE_3__ {int /*<<< orphan*/  (* to_xfer_partial ) (TYPE_1__*,int,char const*,void*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 TYPE_1__ debug_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int,char const*,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  paddr_d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,char const*,void*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONGEST
debug_to_xfer_partial (struct target_ops *ops, enum target_object object,
		       const char *annex, void *readbuf, const void *writebuf,
		       ULONGEST offset, LONGEST len)
{
  LONGEST retval;

  retval = debug_target.to_xfer_partial (&debug_target, object, annex,
					 readbuf, writebuf, offset, len);

  fprintf_unfiltered (gdb_stdlog,
		      "target_xfer_partial (%d, %s, 0x%lx,  0x%lx,  0x%s, %s) = %s\n",
		      (int) object, (annex ? annex : "(null)"),
		      (long) readbuf, (long) writebuf, paddr_nz (offset),
		      paddr_d (len), paddr_d (retval));

  return retval;
}