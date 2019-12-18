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
typedef  int u_int ;

/* Variables and functions */
 int CLIENT_FQDN_FLAGS_E ; 
 int CLIENT_FQDN_FLAGS_N ; 
 int CLIENT_FQDN_FLAGS_O ; 
 int CLIENT_FQDN_FLAGS_S ; 

__attribute__((used)) static char *
client_fqdn_flags(u_int flags)
{
	static char buf[8+1];
	int i = 0;

	if (flags & CLIENT_FQDN_FLAGS_S)
		buf[i++] = 'S';
	if (flags & CLIENT_FQDN_FLAGS_O)
		buf[i++] = 'O';
	if (flags & CLIENT_FQDN_FLAGS_E)
		buf[i++] = 'E';
	if (flags & CLIENT_FQDN_FLAGS_N)
		buf[i++] = 'N';
	buf[i] = '\0';

	return buf;
}