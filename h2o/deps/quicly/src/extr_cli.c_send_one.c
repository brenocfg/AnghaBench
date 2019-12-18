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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct msghdr {int msg_iovlen; struct iovec* msg_iov; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_5__ {int /*<<< orphan*/  sa; } ;
struct TYPE_7__ {TYPE_2__ data; TYPE_1__ dest; } ;
typedef  TYPE_3__ quicly_datagram_t ;
typedef  int /*<<< orphan*/  mess ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  hexdump (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quicly_get_socklen (int /*<<< orphan*/ *) ; 
 scalar_t__ sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int verbosity ; 

__attribute__((used)) static int send_one(int fd, quicly_datagram_t *p)
{
    int ret;
    struct msghdr mess;
    struct iovec vec;
    memset(&mess, 0, sizeof(mess));
    mess.msg_name = &p->dest.sa;
    mess.msg_namelen = quicly_get_socklen(&p->dest.sa);
    vec.iov_base = p->data.base;
    vec.iov_len = p->data.len;
    mess.msg_iov = &vec;
    mess.msg_iovlen = 1;
    if (verbosity >= 2)
        hexdump("sendmsg", vec.iov_base, vec.iov_len);
    while ((ret = (int)sendmsg(fd, &mess, 0)) == -1 && errno == EINTR)
        ;
    return ret;
}