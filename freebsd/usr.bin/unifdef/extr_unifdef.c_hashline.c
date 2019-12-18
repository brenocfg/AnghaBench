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

/* Variables and functions */
 int /*<<< orphan*/  closeio () ; 
 int fprintf (int /*<<< orphan*/ ,char*,int,char*,...) ; 
 char* linefile ; 
 int linenum ; 
 char* newline ; 
 int /*<<< orphan*/  output ; 

__attribute__((used)) static void
hashline(void)
{
	int e;

	if (linefile == NULL)
		e = fprintf(output, "#line %d%s", linenum, newline);
	else
		e = fprintf(output, "#line %d \"%s\"%s",
		    linenum, linefile, newline);
	if (e < 0)
		closeio();
}