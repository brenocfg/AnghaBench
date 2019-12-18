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
typedef  scalar_t__ gdb_wince_id ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ skip_next_id ; 
 int sockread (int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD
getdword (LPCWSTR huh, int s, gdb_wince_id what_this)
{
  DWORD n;
  gdb_wince_id what;

  if (skip_next_id)
    skip_next_id = 0;
  else
    do
      if (sockread (huh, s, &what, sizeof (what)) != sizeof (what))
	stub_error (L"error getting record type from host - %s.", huh);
    while (what_this != what);

  if (sockread (huh, s, &n, sizeof (n)) != sizeof (n))
    stub_error (L"error getting %s from host.", huh);

  return n;
}