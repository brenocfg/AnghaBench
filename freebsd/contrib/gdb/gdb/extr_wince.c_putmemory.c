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
typedef  scalar_t__ gdb_wince_len ;
typedef  int /*<<< orphan*/  gdb_wince_id ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  putlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sockwrite (int /*<<< orphan*/ ,void const*,scalar_t__) ; 
 int /*<<< orphan*/  stub_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
putmemory (LPCSTR huh, gdb_wince_id what, const void *mem, gdb_wince_len len)
{
  putlen (huh, what, len);
  if (((short) len > 0) && sockwrite (huh, mem, len) != len)
    stub_error ("error writing %s to host.", huh);
}