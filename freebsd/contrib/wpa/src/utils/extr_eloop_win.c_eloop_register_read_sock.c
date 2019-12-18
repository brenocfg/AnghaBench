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
struct eloop_sock {int sock; scalar_t__ event; int /*<<< orphan*/  handler; void* user_data; void* eloop_data; } ;
typedef  int /*<<< orphan*/  eloop_sock_handler ;
typedef  scalar_t__ WSAEVENT ;
struct TYPE_2__ {int reader_count; int max_sock; int reader_table_changed; struct eloop_sock* readers; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_READ ; 
 int /*<<< orphan*/  WSACloseEvent (scalar_t__) ; 
 scalar_t__ WSACreateEvent () ; 
 scalar_t__ WSAEventSelect (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int WSAGetLastError () ; 
 scalar_t__ WSA_INVALID_EVENT ; 
 TYPE_1__ eloop ; 
 scalar_t__ eloop_prepare_handles () ; 
 struct eloop_sock* os_realloc_array (struct eloop_sock*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int eloop_register_read_sock(int sock, eloop_sock_handler handler,
			     void *eloop_data, void *user_data)
{
	WSAEVENT event;
	struct eloop_sock *tmp;

	if (eloop_prepare_handles())
		return -1;

	event = WSACreateEvent();
	if (event == WSA_INVALID_EVENT) {
		printf("WSACreateEvent() failed: %d\n", WSAGetLastError());
		return -1;
	}

	if (WSAEventSelect(sock, event, FD_READ)) {
		printf("WSAEventSelect() failed: %d\n", WSAGetLastError());
		WSACloseEvent(event);
		return -1;
	}
	tmp = os_realloc_array(eloop.readers, eloop.reader_count + 1,
			       sizeof(struct eloop_sock));
	if (tmp == NULL) {
		WSAEventSelect(sock, event, 0);
		WSACloseEvent(event);
		return -1;
	}

	tmp[eloop.reader_count].sock = sock;
	tmp[eloop.reader_count].eloop_data = eloop_data;
	tmp[eloop.reader_count].user_data = user_data;
	tmp[eloop.reader_count].handler = handler;
	tmp[eloop.reader_count].event = event;
	eloop.reader_count++;
	eloop.readers = tmp;
	if (sock > eloop.max_sock)
		eloop.max_sock = sock;
	eloop.reader_table_changed = 1;

	return 0;
}