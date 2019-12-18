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
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logprintf (char*) ; 
 char* refdir ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 

void
copy_reference_file(const char *name)
{
	char buff[1024];
	FILE *in, *out;
	size_t rbytes;

	sprintf(buff, "%s/%s", refdir, name);
	in = fopen(buff, "rb");
	failure("Couldn't open reference file %s", buff);
	assert(in != NULL);
	if (in == NULL)
		return;
	/* Now, decode the rest and write it. */
	/* Not a lot of error checking here; the input better be right. */
	out = fopen(name, "wb");
	while ((rbytes = fread(buff, 1, sizeof(buff), in)) > 0) {
		if (fwrite(buff, 1, rbytes, out) != rbytes) {
			logprintf("Error: fwrite\n");
			break;
		}
	}
	fclose(out);
	fclose(in);
}