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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  testingT ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vprintf (char const*,int /*<<< orphan*/ ) ; 

void testingprivTLogvfFull(testingT *t, const char *file, int line, const char *format, va_list ap)
{
	// TODO extract filename from file
	printf("\t%s:%d: ", file, line);
	// TODO split into lines separated by \n\t\t and trimming trailing empty lines
	vprintf(format, ap);
	printf("\n");
}