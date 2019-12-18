#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_4__ {int fd; char const* name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int EXIT_FAILURE ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int caph_limit_stdout () ; 
 scalar_t__ caph_rights_limit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 TYPE_1__* head ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static void
add(int fd, const char *name)
{
	LIST *p;
	cap_rights_t rights;

	if (fd == STDOUT_FILENO) {
		if (caph_limit_stdout() == -1)
			err(EXIT_FAILURE, "unable to limit stdout");
	} else {
		cap_rights_init(&rights, CAP_WRITE, CAP_FSTAT);
		if (caph_rights_limit(fd, &rights) < 0)
			err(EXIT_FAILURE, "unable to limit rights");
	}

	if ((p = malloc(sizeof(LIST))) == NULL)
		err(1, "malloc");
	p->fd = fd;
	p->name = name;
	p->next = head;
	head = p;
}