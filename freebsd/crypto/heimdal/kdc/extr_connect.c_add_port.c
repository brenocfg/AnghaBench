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
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {int type; int port; int family; } ;

/* Variables and functions */
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 size_t num_ports ; 
 TYPE_1__* ports ; 
 TYPE_1__* realloc (TYPE_1__*,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
add_port(krb5_context context,
	 int family, int port, const char *protocol)
{
    int type;
    size_t i;

    if(strcmp(protocol, "udp") == 0)
	type = SOCK_DGRAM;
    else if(strcmp(protocol, "tcp") == 0)
	type = SOCK_STREAM;
    else
	return;
    for(i = 0; i < num_ports; i++){
	if(ports[i].type == type
	   && ports[i].port == port
	   && ports[i].family == family)
	    return;
    }
    ports = realloc(ports, (num_ports + 1) * sizeof(*ports));
    if (ports == NULL)
	krb5_err (context, 1, errno, "realloc");
    ports[num_ports].family = family;
    ports[num_ports].type   = type;
    ports[num_ports].port   = port;
    num_ports++;
}