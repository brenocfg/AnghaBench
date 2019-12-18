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
struct autofs_daemon_done {int add_wildcards; int add_error; int /*<<< orphan*/  add_id; } ;
typedef  int /*<<< orphan*/  add ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFSDONE ; 
 int /*<<< orphan*/  autofs_fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct autofs_daemon_done*) ; 
 int /*<<< orphan*/  log_debugx (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/  memset (struct autofs_daemon_done*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_id ; 

__attribute__((used)) static void
done(int request_error, bool wildcards)
{
	struct autofs_daemon_done add;
	int error;

	memset(&add, 0, sizeof(add));
	add.add_id = request_id;
	add.add_wildcards = wildcards;
	add.add_error = request_error;

	log_debugx("completing request %d with error %d",
	    request_id, request_error);

	error = ioctl(autofs_fd, AUTOFSDONE, &add);
	if (error != 0)
		log_warn("AUTOFSDONE");
}