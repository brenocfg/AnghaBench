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
typedef  int /*<<< orphan*/  gdb_wince_result ;
typedef  int gdb_wince_len ;
typedef  int /*<<< orphan*/  gdb_wince_id ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  putmemory (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static void
putresult (LPCWSTR huh, gdb_wince_result res, int s, gdb_wince_id what, const void *mem, gdb_wince_len len)
{
  if (!res)
    len = -(int) GetLastError ();
  putmemory (huh, s, what, mem, len);
}