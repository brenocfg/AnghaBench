#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct transport {TYPE_1__* vtable; } ;
struct TYPE_2__ {int (* connect ) (struct transport*,char const*,char const*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int stub1 (struct transport*,char const*,char const*,int*) ; 

int transport_connect(struct transport *transport, const char *name,
		      const char *exec, int fd[2])
{
	if (transport->vtable->connect)
		return transport->vtable->connect(transport, name, exec, fd);
	else
		die(_("operation not supported by protocol"));
}