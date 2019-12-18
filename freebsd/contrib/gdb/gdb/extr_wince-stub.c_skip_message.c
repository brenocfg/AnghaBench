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
typedef  int /*<<< orphan*/  wchar_t ;
struct skipper {int nskip; int /*<<< orphan*/ * s; } ;
typedef  int /*<<< orphan*/  s ;
struct TYPE_5__ {int nDebugStringLength; int /*<<< orphan*/  lpDebugStringData; } ;
struct TYPE_6__ {TYPE_1__ DebugString; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_3__ DEBUG_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  ReadProcessMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curproc ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct skipper* skippy ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ *) ; 
 scalar_t__ wcsncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
skip_message (DEBUG_EVENT *ev)
{
  char s[80];
  DWORD nread;
  struct skipper *skp;
  int nbytes = ev->u.DebugString.nDebugStringLength;

  if (nbytes > sizeof(s))
    nbytes = sizeof(s);

  memset (s, 0, sizeof (s));
  if (!ReadProcessMemory (curproc, ev->u.DebugString.lpDebugStringData,
			  s, nbytes, &nread))
    return 0;

  for (skp = skippy; skp->s != NULL; skp++)
    if (wcsncmp ((wchar_t *) s, skp->s, wcslen (skp->s)) == 0)
      return skp->nskip;

  return 0;
}