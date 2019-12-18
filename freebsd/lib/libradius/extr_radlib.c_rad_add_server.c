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
struct rad_handle {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEAD_TIME ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int rad_add_server_ex (struct rad_handle*,char const*,int,char const*,int,int,int /*<<< orphan*/ ,struct in_addr*) ; 

int
rad_add_server(struct rad_handle *h, const char *host, int port,
    const char *secret, int timeout, int tries)
{
    	struct in_addr bindto;
	bindto.s_addr = INADDR_ANY;

	return rad_add_server_ex(h, host, port, secret, timeout, tries,
		DEAD_TIME, &bindto);
}