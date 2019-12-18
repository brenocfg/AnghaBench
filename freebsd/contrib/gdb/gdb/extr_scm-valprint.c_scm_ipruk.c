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
struct ui_file {int dummy; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 scalar_t__ SCM_CAR (int /*<<< orphan*/ ) ; 
 scalar_t__ SCM_CDR (int /*<<< orphan*/ ) ; 
 scalar_t__ SCM_CELLP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 char* paddr_nz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scm_ipruk (char *hdr, LONGEST ptr, struct ui_file *stream)
{
  fprintf_filtered (stream, "#<unknown-%s", hdr);
#define SCM_SIZE TYPE_LENGTH (builtin_type_scm)
  if (SCM_CELLP (ptr))
    fprintf_filtered (stream, " (0x%lx . 0x%lx) @",
		      (long) SCM_CAR (ptr), (long) SCM_CDR (ptr));
  fprintf_filtered (stream, " 0x%s>", paddr_nz (ptr));
}