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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 char* _PATH_UNIX_X ; 
 int connect_local_xsocket_path (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
connect_local_xsocket(u_int dnr)
{
	char buf[1024];
	snprintf(buf, sizeof buf, _PATH_UNIX_X, dnr);
	return connect_local_xsocket_path(buf);
}