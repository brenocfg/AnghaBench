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
struct servent {int s_port; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  add_port (int /*<<< orphan*/ ,int,int,char const*) ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct servent* roken_getservbyname (char const*,char const*) ; 
 int /*<<< orphan*/  strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_port_string (krb5_context context,
		 int family, const char *str, const char *protocol)
{
    struct servent *sp;
    int port;

    sp = roken_getservbyname (str, protocol);
    if (sp != NULL) {
	port = sp->s_port;
    } else {
	char *end;

	port = htons(strtol(str, &end, 0));
	if (end == str)
	    return;
    }
    add_port (context, family, port, protocol);
}