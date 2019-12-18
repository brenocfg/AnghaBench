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
typedef  int /*<<< orphan*/  outs ;
typedef  int gdb_wince_len ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xrealloc (int /*<<< orphan*/ *,int) ; 

LPWSTR
towide (const char *s, gdb_wince_len * out_len)
{
  static int n = -1;
  static LPWSTR outs[8] =
  {NULL /*, NULL, etc. */ };
  gdb_wince_len dummy;

  if (!out_len)
    out_len = &dummy;

  /* First determine the length required to hold the converted string. */
  *out_len = sizeof (WCHAR) * MultiByteToWideChar (CP_ACP, 0, s, -1, NULL, 0);
  if (!*out_len)
    return NULL;		/* The conversion failed */

  if (++n >= (sizeof (outs) / sizeof (outs[0])))
    n = 0;			/* wrap */

  /* Allocate space for the converted string, reusing any previously allocated
     space, if applicable. Note that if outs[n] is NULL, xrealloc will act as
     a malloc (under cygwin, at least).
   */
  outs[n] = (LPWSTR) xrealloc (outs[n], *out_len);
  memset (outs[n], 0, *out_len);
  (void) MultiByteToWideChar (CP_ACP, 0, s, -1, outs[n], *out_len);
  return outs[n];
}