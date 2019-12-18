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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ getlen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool (unsigned int) ; 
 scalar_t__ sockread (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub_error (char*) ; 

__attribute__((used)) static LPWSTR
getmemory (LPCWSTR huh, int s, gdb_wince_id what, gdb_wince_len *inlen)
{
  LPVOID p;
  gdb_wince_len dummy;

  if (!inlen)
    inlen = &dummy;

  *inlen = getlen (huh, s, what);

  p = mempool ((unsigned int) *inlen);	/* FIXME: check for error */

  if ((gdb_wince_len) sockread (huh, s, p, *inlen) != *inlen)
    stub_error (L"error getting string from host.");

  return p;
}