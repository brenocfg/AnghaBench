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
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 int /*<<< orphan*/  NL ; 
 int /*<<< orphan*/  TAB ; 
 int /*<<< orphan*/  nlines ; 
 int /*<<< orphan*/  pjson (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
pclose_arr (GJSON * json, int sp, int last)
{
  if (!last)
    pjson (json, "%.*s%.*s],%.*s", nlines, NL, sp, TAB, nlines, NL);
  else
    pjson (json, "%.*s%.*s]", nlines, NL, sp, TAB);
}