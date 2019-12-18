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
 int LineNo ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  _write (int /*<<< orphan*/ ,char*,int) ; 
 char* path_fstab ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* strerror (int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
error(int err)
{
	char *p;
	char num[30];

	(void)_write(STDERR_FILENO, "fstab: ", 7);
	(void)_write(STDERR_FILENO, path_fstab, strlen(path_fstab));
	(void)_write(STDERR_FILENO, ":", 1);
	sprintf(num, "%d: ", LineNo);
	(void)_write(STDERR_FILENO, num, strlen(num));
	p = strerror(err);
	(void)_write(STDERR_FILENO, p, strlen(p));
	(void)_write(STDERR_FILENO, "\n", 1);
}