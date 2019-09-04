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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  NL ; 
 int /*<<< orphan*/  TAB ; 
 int /*<<< orphan*/  fpjson (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlines ; 

void
fpopen_arr_attr (FILE * fp, const char *attr, int sp)
{
  /* open object attribute */
  fpjson (fp, "%.*s\"%s\": [%.*s", sp, TAB, attr, nlines, NL);
}