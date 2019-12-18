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
 int /*<<< orphan*/  cookedprint (int,size_t,char const*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ rawmode ; 
 int /*<<< orphan*/  rawprint (int,size_t,char const*,int,int,int /*<<< orphan*/ *) ; 

void
printvars(
	size_t length,
	const char *data,
	int status,
	int sttype,
	int quiet,
	FILE *fp
	)
{
	if (rawmode)
	    rawprint(sttype, length, data, status, quiet, fp);
	else
	    cookedprint(sttype, length, data, status, quiet, fp);
}