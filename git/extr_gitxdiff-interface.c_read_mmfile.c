#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; } ;
struct TYPE_3__ {size_t size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ mmfile_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int error (char*,char const*) ; 
 int error_errno (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  xmalloc (size_t) ; 
 size_t xsize_t (int /*<<< orphan*/ ) ; 

int read_mmfile(mmfile_t *ptr, const char *filename)
{
	struct stat st;
	FILE *f;
	size_t sz;

	if (stat(filename, &st))
		return error_errno("Could not stat %s", filename);
	if ((f = fopen(filename, "rb")) == NULL)
		return error_errno("Could not open %s", filename);
	sz = xsize_t(st.st_size);
	ptr->ptr = xmalloc(sz ? sz : 1);
	if (sz && fread(ptr->ptr, sz, 1, f) != 1) {
		fclose(f);
		return error("Could not read %s", filename);
	}
	fclose(f);
	ptr->size = sz;
	return 0;
}