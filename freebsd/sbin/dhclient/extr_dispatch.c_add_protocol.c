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
struct protocol {int fd; void (* handler ) (struct protocol*) ;struct protocol* next; void* local; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char const*) ; 
 struct protocol* malloc (int) ; 
 struct protocol* protocols ; 

void
add_protocol(const char *name, int fd, void (*handler)(struct protocol *),
    void *local)
{
	struct protocol *p;

	p = malloc(sizeof(*p));
	if (!p)
		error("can't allocate protocol struct for %s", name);

	p->fd = fd;
	p->handler = handler;
	p->local = local;
	p->next = protocols;
	protocols = p;
}