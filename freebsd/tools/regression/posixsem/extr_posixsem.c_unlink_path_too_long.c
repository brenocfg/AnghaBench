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
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ksem_unlink_should_fail (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 

__attribute__((used)) static void
unlink_path_too_long(void)
{
	char *page;

	page = malloc(MAXPATHLEN + 1);
	memset(page, 'a', MAXPATHLEN);
	page[MAXPATHLEN] = '\0';
	ksem_unlink_should_fail(page, ENAMETOOLONG);
	free(page);
}