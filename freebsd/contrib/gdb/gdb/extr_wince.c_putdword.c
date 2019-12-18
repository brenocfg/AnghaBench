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
typedef  int /*<<< orphan*/  what ;
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  gdb_wince_id ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int sockwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
putdword (LPCSTR huh, gdb_wince_id what, DWORD n)
{
  if (sockwrite (huh, &what, sizeof (what)) != sizeof (what))
    stub_error ("error writing record id to host for %s", huh);
  if (sockwrite (huh, &n, sizeof (n)) != sizeof (n))
    stub_error ("error writing %s to host.", huh);
}