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
struct hashfile {int check_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  die_errno (char*,...) ; 
 struct hashfile* hashfd (int,char const*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

struct hashfile *hashfd_check(const char *name)
{
	int sink, check;
	struct hashfile *f;

	sink = open("/dev/null", O_WRONLY);
	if (sink < 0)
		die_errno("unable to open /dev/null");
	check = open(name, O_RDONLY);
	if (check < 0)
		die_errno("unable to open '%s'", name);
	f = hashfd(sink, name);
	f->check_fd = check;
	return f;
}