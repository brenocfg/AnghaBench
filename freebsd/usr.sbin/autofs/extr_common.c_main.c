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
 char* basename (char*) ; 
 int /*<<< orphan*/  log_errx (int,char*) ; 
 int main_automount (int,char**) ; 
 int main_automountd (int,char**) ; 
 int main_autounmountd (int,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
main(int argc, char **argv)
{
	char *cmdname;

	if (argv[0] == NULL)
		log_errx(1, "NULL command name");

	cmdname = basename(argv[0]);

	if (strcmp(cmdname, "automount") == 0)
		return (main_automount(argc, argv));
	else if (strcmp(cmdname, "automountd") == 0)
		return (main_automountd(argc, argv));
	else if (strcmp(cmdname, "autounmountd") == 0)
		return (main_autounmountd(argc, argv));
	else
		log_errx(1, "binary name should be either \"automount\", "
		    "\"automountd\", or \"autounmountd\"");
}