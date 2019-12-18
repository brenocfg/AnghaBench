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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 

char * os_readfile(const char *name, size_t *len)
{
	FILE *f;
	char *buf;
	long pos;

	f = fopen(name, "rb");
	if (f == NULL)
		return NULL;

	if (fseek(f, 0, SEEK_END) < 0 || (pos = ftell(f)) < 0) {
		fclose(f);
		return NULL;
	}
	*len = pos;
	if (fseek(f, 0, SEEK_SET) < 0) {
		fclose(f);
		return NULL;
	}

	buf = os_malloc(*len);
	if (buf == NULL) {
		fclose(f);
		return NULL;
	}

	if (fread(buf, 1, *len, f) != *len) {
		fclose(f);
		os_free(buf);
		return NULL;
	}

	fclose(f);

	return buf;
}