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

/* Variables and functions */
 int /*<<< orphan*/  SOCK_STREAM ; 
 int setup_client (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
setup_tcp_client(int domain, int port)
{

	return (setup_client(domain, SOCK_STREAM, port));
}