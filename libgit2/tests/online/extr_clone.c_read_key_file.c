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
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (char*,long,int,int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 char* malloc (long) ; 

__attribute__((used)) static char *read_key_file(const char *path)
{
	FILE *f;
	char *buf;
	long key_length;

	if (!path || !*path)
		return NULL;

	cl_assert((f = fopen(path, "r")) != NULL);
	cl_assert(fseek(f, 0, SEEK_END) != -1);
	cl_assert((key_length = ftell(f)) != -1);
	cl_assert(fseek(f, 0, SEEK_SET) != -1);
	cl_assert((buf = malloc(key_length)) != NULL);
	cl_assert(fread(buf, key_length, 1, f) == 1);
	fclose(f);

	return buf;
}