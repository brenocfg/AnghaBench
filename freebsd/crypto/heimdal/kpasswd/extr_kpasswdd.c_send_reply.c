#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr {int dummy; } ;
struct msghdr {int msg_namelen; int msg_iovlen; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; void* msg_name; } ;
struct iovec {char* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  msghdr ;
struct TYPE_4__ {int length; char* data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  iov ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
send_reply (int s,
	    struct sockaddr *sa,
	    int sa_size,
	    krb5_data *ap_rep,
	    krb5_data *rest)
{
    struct msghdr msghdr;
    struct iovec iov[3];
    uint16_t len, ap_rep_len;
    u_char header[6];
    u_char *p;

    if (ap_rep)
	ap_rep_len = ap_rep->length;
    else
	ap_rep_len = 0;

    len = 6 + ap_rep_len + rest->length;
    p = header;
    *p++ = (len >> 8) & 0xFF;
    *p++ = (len >> 0) & 0xFF;
    *p++ = 0;
    *p++ = 1;
    *p++ = (ap_rep_len >> 8) & 0xFF;
    *p++ = (ap_rep_len >> 0) & 0xFF;

    memset (&msghdr, 0, sizeof(msghdr));
    msghdr.msg_name       = (void *)sa;
    msghdr.msg_namelen    = sa_size;
    msghdr.msg_iov        = iov;
    msghdr.msg_iovlen     = sizeof(iov)/sizeof(*iov);
#if 0
    msghdr.msg_control    = NULL;
    msghdr.msg_controllen = 0;
#endif

    iov[0].iov_base       = (char *)header;
    iov[0].iov_len        = 6;
    if (ap_rep_len) {
	iov[1].iov_base   = ap_rep->data;
	iov[1].iov_len    = ap_rep->length;
    } else {
	iov[1].iov_base   = NULL;
	iov[1].iov_len    = 0;
    }
    iov[2].iov_base       = rest->data;
    iov[2].iov_len        = rest->length;

    if (sendmsg (s, &msghdr, 0) < 0)
	krb5_warn (context, errno, "sendmsg");
}