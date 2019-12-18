#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
 scalar_t__ COMPLETE ; 
 int /*<<< orphan*/  IPTOS_THROUGHPUT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int SO_DEBUG ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ command (char*) ; 
 scalar_t__ connect (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int data ; 
 TYPE_1__* data_addr ; 
 int /*<<< orphan*/  hisctladdr ; 
 TYPE_3__* myctladdr ; 
 int options ; 
 int parse_epsv (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_pasv (struct sockaddr_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasv ; 
 int /*<<< orphan*/  printf (char*) ; 
 int sendport ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_get_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_address_and_port (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_set_debug (int) ; 
 int /*<<< orphan*/  socket_set_tos (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_sockaddr_size (TYPE_1__*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
passive_mode (void)
{
    int port;

    data = socket (myctladdr->sa_family, SOCK_STREAM, 0);
    if (data < 0) {
	warn ("socket");
	return (1);
    }
    if (options & SO_DEBUG)
	socket_set_debug (data);
    if (command ("EPSV") != COMPLETE) {
	if (command ("PASV") != COMPLETE) {
	    printf ("Passive mode refused.\n");
	    goto bad;
	}
    }

    /*
     * Parse the reply to EPSV or PASV
     */

    port = parse_epsv (pasv);
    if (port > 0) {
	data_addr->sa_family = myctladdr->sa_family;
	socket_set_address_and_port (data_addr,
				     socket_get_address (hisctladdr),
				     port);
    } else {
	if (parse_pasv ((struct sockaddr_in *)data_addr, pasv) < 0)
	    goto bad;
    }

    if (connect (data, data_addr, socket_sockaddr_size (data_addr)) < 0) {
	warn ("connect");
	goto bad;
    }
#ifdef IPTOS_THROUGHPUT
    socket_set_tos (data, IPTOS_THROUGHPUT);
#endif
    return (0);
bad:
    close (data);
    data = -1;
    sendport = 1;
    return (1);
}