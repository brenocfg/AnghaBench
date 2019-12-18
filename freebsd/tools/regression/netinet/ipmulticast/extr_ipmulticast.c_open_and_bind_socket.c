#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sa_len; } ;
struct TYPE_4__ {TYPE_3__ sa; } ;
typedef  TYPE_1__ sockunion_t ;
typedef  int /*<<< orphan*/  optval ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int bind (int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ doreuseport ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
open_and_bind_socket(sockunion_t *bsu)
{
	int	 error, optval, sock;

	sock = -1;

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == -1) {
		warn("socket");
		return (-1);
	}

	if (doreuseport) {
		optval = 1;
		if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &optval,
		    sizeof(optval)) < 0) {
			warn("setsockopt SO_REUSEPORT");
			close(sock);
			return (-1);
		}
	}

	if (bsu != NULL) {
		error = bind(sock, &bsu->sa, bsu->sa.sa_len);
		if (error == -1) {
			warn("bind");
			close(sock);
			return (-1);
		}
	}

	return (sock);
}