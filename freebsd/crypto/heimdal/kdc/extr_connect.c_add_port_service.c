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
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  add_port (int /*<<< orphan*/ ,int,int,char const*) ; 
 int krb5_getportbyname (int /*<<< orphan*/ ,char const*,char const*,int) ; 

__attribute__((used)) static void
add_port_service(krb5_context context,
		 int family, const char *service, int port,
		 const char *protocol)
{
    port = krb5_getportbyname (context, service, protocol, port);
    add_port (context, family, port, protocol);
}