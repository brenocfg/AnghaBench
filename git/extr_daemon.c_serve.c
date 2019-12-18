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
struct string_list {int dummy; } ;
struct socketlist {scalar_t__ nr; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct credentials {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int) ; 
 int /*<<< orphan*/  drop_privileges (struct credentials*) ; 
 int /*<<< orphan*/  loginfo (char*) ; 
 int service_loop (struct socketlist*) ; 
 int /*<<< orphan*/  socksetup (struct string_list*,int,struct socketlist*) ; 

__attribute__((used)) static int serve(struct string_list *listen_addr, int listen_port,
    struct credentials *cred)
{
	struct socketlist socklist = { NULL, 0, 0 };

	socksetup(listen_addr, listen_port, &socklist);
	if (socklist.nr == 0)
		die("unable to allocate any listen sockets on port %u",
		    listen_port);

	drop_privileges(cred);

	loginfo("Ready to rumble");

	return service_loop(&socklist);
}