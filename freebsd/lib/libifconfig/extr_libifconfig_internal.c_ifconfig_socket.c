#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  errcode; void* errtype; } ;
struct TYPE_5__ {int* sockets; TYPE_1__ error; } ;
typedef  TYPE_2__ ifconfig_handle_t ;

/* Variables and functions */
 int const AF_MAX ; 
 int /*<<< orphan*/  EINVAL ; 
 void* SOCKET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  errno ; 
 int socket (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ifconfig_socket(ifconfig_handle_t *h, const int addressfamily, int *s)
{

	if (addressfamily > AF_MAX) {
		h->error.errtype = SOCKET;
		h->error.errcode = EINVAL;
		return (-1);
	}

	if (h->sockets[addressfamily] != -1) {
		*s = h->sockets[addressfamily];
		return (0);
	}

	/* We don't have a socket of that type available. Create one. */
	h->sockets[addressfamily] = socket(addressfamily, SOCK_DGRAM, 0);
	if (h->sockets[addressfamily] == -1) {
		h->error.errtype = SOCKET;
		h->error.errcode = errno;
		return (-1);
	}

	*s = h->sockets[addressfamily];
	return (0);
}