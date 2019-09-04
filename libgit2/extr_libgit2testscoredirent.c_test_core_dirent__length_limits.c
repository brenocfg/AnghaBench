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
 int FILENAME_MAX ; 
 int /*<<< orphan*/  cl_must_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 scalar_t__ git__malloc (int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  p_creat (char*,int) ; 

void test_core_dirent__length_limits(void)
{
	char *big_filename = (char *)git__malloc(FILENAME_MAX + 1);
	memset(big_filename, 'a', FILENAME_MAX + 1);
	big_filename[FILENAME_MAX] = 0;

	cl_must_fail(p_creat(big_filename, 0666));

	git__free(big_filename);
}