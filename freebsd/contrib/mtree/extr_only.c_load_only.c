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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FPARSELN_UNESCALL ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill (char*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* fparseln (int /*<<< orphan*/ *,size_t*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hash_find (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_insert (char*,int /*<<< orphan*/ ) ; 
 int loaded ; 

void
load_only(const char *fname)
{
	FILE *fp;
	char *line;
	size_t len, lineno;

	if ((fp = fopen(fname, "r")) == NULL)
		err(1, "Cannot open `%s'", fname);

	while ((line = fparseln(fp, &len, &lineno, NULL, FPARSELN_UNESCALL))) {
		uint32_t h;
		if (hash_find(line, &h))
			err(1, "Duplicate entry %s", line);
		hash_insert(line, h);
		fill(line);
		free(line);
	}

	fclose(fp);
	loaded = true;
}