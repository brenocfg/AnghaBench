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
 int listen (int,int) ; 
 int /*<<< orphan*/  setupsockbufsize (int) ; 

int
ftp_listen(int sock, int backlog)
{

	setupsockbufsize(sock);
	return (listen(sock, backlog));
}