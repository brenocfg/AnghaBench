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

/* Variables and functions */
 char* _getprogname () ; 
 int /*<<< orphan*/ * err_file ; 
 int /*<<< orphan*/  err_set_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

void
vwarnc(int code, const char *fmt, va_list ap)
{
	if (err_file == NULL)
		err_set_file(NULL);
	fprintf(err_file, "%s: ", _getprogname());
	if (fmt != NULL) {
		vfprintf(err_file, fmt, ap);
		fprintf(err_file, ": ");
	}
	fprintf(err_file, "%s\n", strerror(code));
}