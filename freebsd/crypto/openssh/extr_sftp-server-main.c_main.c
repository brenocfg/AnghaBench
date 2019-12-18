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
typedef  int /*<<< orphan*/  u_long ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  sanitise_stdfd () ; 
 int sftp_server_main (int,char**,struct passwd*) ; 
 int /*<<< orphan*/  ssh_malloc_init () ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char **argv)
{
	struct passwd *user_pw;

	ssh_malloc_init();	/* must be called before any mallocs */
	/* Ensure that fds 0, 1 and 2 are open or directed to /dev/null */
	sanitise_stdfd();

	if ((user_pw = getpwuid(getuid())) == NULL) {
		fprintf(stderr, "No user found for uid %lu\n",
		    (u_long)getuid());
		return 1;
	}

	return (sftp_server_main(argc, argv, user_pw));
}