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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fwrite (void*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logprintf (char*,char const*) ; 

void
dumpfile(const char *filename, void *data, size_t len)
{
	ssize_t bytes_written;
	FILE *f;

	f = fopen(filename, "wb");
	if (f == NULL) {
		logprintf("Can't open file %s for writing\n", filename);
		return;
	}
	bytes_written = fwrite(data, 1, len, f);
	if (bytes_written < (ssize_t)len)
		logprintf("Can't write file %s\n", filename);
	fclose(f);
}