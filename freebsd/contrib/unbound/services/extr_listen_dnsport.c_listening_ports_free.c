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
struct listen_port {int fd; struct listen_port* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  free (struct listen_port*) ; 

void listening_ports_free(struct listen_port* list)
{
	struct listen_port* nx;
	while(list) {
		nx = list->next;
		if(list->fd != -1) {
#ifndef USE_WINSOCK
			close(list->fd);
#else
			closesocket(list->fd);
#endif
		}
		free(list);
		list = nx;
	}
}