#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msghdr {int /*<<< orphan*/  to_addr_len; int /*<<< orphan*/  to_addr; int /*<<< orphan*/  msg_iovlen; int /*<<< orphan*/  msg_iov; } ;
struct TYPE_3__ {int /*<<< orphan*/  pending_send; int /*<<< orphan*/  pending_iocp; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ isc_socket_t ;
typedef  int /*<<< orphan*/  SOCKADDR ;
typedef  int /*<<< orphan*/  LPWSAOVERLAPPED ;
typedef  int /*<<< orphan*/  IoCompletionInfo ;
typedef  int DWORD ;

/* Variables and functions */
#define  NO_ERROR 131 
 int SOCKET_ERROR ; 
 int WSAGetLastError () ; 
 int WSASendTo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  WSA_IO_INCOMPLETE 130 
#define  WSA_IO_PENDING 129 
#define  WSA_WAIT_IO_COMPLETION 128 

int
internal_sendmsg(isc_socket_t *sock, IoCompletionInfo *lpo,
		 struct msghdr *messagehdr, int flags, int *Error)
{
	int Result;
	DWORD BytesSent;
	DWORD Flags = flags;
	int total_sent;

	*Error = 0;
	Result = WSASendTo(sock->fd, messagehdr->msg_iov,
			   messagehdr->msg_iovlen, &BytesSent,
			   Flags, (SOCKADDR *)&messagehdr->to_addr,
			   messagehdr->to_addr_len, (LPWSAOVERLAPPED)lpo,
			   NULL);

	total_sent = (int)BytesSent;

	/* Check for errors.*/
	if (Result == SOCKET_ERROR) {
		*Error = WSAGetLastError();

		switch (*Error) {
		case WSA_IO_INCOMPLETE:
		case WSA_WAIT_IO_COMPLETION:
		case WSA_IO_PENDING:
		case NO_ERROR:		/* Strange, but okay */
			sock->pending_iocp++;
			sock->pending_send++;
			break;

		default:
			return (-1);
			break;
		}
	} else {
		sock->pending_iocp++;
		sock->pending_send++;
	}

	if (lpo != NULL)
		return (0);
	else
		return (total_sent);
}