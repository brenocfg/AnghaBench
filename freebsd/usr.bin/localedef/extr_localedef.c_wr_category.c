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
 int EOF ; 
 int /*<<< orphan*/  category_file () ; 
 int /*<<< orphan*/  errf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fwrite (void*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int
wr_category(void *buf, size_t sz, FILE *f)
{
	if (!sz) {
		return (0);
	}
	if (fwrite(buf, sz, 1, f) < 1) {
		(void) fclose(f);
		(void) unlink(category_file());
		errf("%s", strerror(errno));
		return (EOF);
	}
	return (0);
}