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
typedef  scalar_t__ WSAEVENT ;

/* Variables and functions */
 int /*<<< orphan*/  FD_READ ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  WSACloseEvent (scalar_t__) ; 
 scalar_t__ WSACreateEvent () ; 
 int /*<<< orphan*/  WSAEventSelect (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int WSAGetLastError () ; 
 scalar_t__ WSA_INVALID_EVENT ; 
 int /*<<< orphan*/  WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void eloop_wait_for_read_sock(int sock)
{
	WSAEVENT event;

	event = WSACreateEvent();
	if (event == WSA_INVALID_EVENT) {
		printf("WSACreateEvent() failed: %d\n", WSAGetLastError());
		return;
	}

	if (WSAEventSelect(sock, event, FD_READ)) {
		printf("WSAEventSelect() failed: %d\n", WSAGetLastError());
		WSACloseEvent(event);
		return ;
	}

	WaitForSingleObject(event, INFINITE);
	WSAEventSelect(sock, event, 0);
	WSACloseEvent(event);
}