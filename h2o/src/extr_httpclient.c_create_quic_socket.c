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
struct sockaddr_in {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  H2O_SOCKET_FLAG_DONT_READ ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ bind (int,void*,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * h2o_evloop_socket_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static h2o_socket_t *create_quic_socket(h2o_loop_t *loop)
{
    int fd;
    struct sockaddr_in sin;

    if ((fd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("failed to create UDP socket");
        exit(EXIT_FAILURE);
    }
    memset(&sin, 0, sizeof(sin));
    if (bind(fd, (void *)&sin, sizeof(sin)) != 0) {
        perror("failed to bind bind UDP socket");
        exit(EXIT_FAILURE);
    }

    return h2o_evloop_socket_create(loop, fd, H2O_SOCKET_FLAG_DONT_READ);
}