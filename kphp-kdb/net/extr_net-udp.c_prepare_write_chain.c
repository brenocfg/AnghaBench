#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  total_bytes; } ;
struct udp_message {int our_ip_idx; struct udp_message* next; TYPE_3__ raw; int /*<<< orphan*/  ipv6; int /*<<< orphan*/  port; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; TYPE_1__ sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {int /*<<< orphan*/  sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; TYPE_1__ sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct TYPE_6__ {int msg_namelen; int msg_iovlen; scalar_t__ msg_controllen; int /*<<< orphan*/  msg_control; int /*<<< orphan*/  msg_flags; scalar_t__ msg_iov; struct sockaddr_in6* msg_name; } ;
struct our_mmsghdr {TYPE_2__ msg_hdr; int /*<<< orphan*/  msg_len; } ;
struct TYPE_8__ {scalar_t__ msg_controllen; int /*<<< orphan*/  msg_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int MAX_OUR_IPS ; 
 scalar_t__ MAX_UDP_SEND_BUFFERS ; 
 int /*<<< orphan*/  MAX_UDP_SEND_DATAGRAM ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  extract_4in6 (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 scalar_t__ is_4in6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* outbound_src_ip_hdr ; 
 int rwm_prepare_iovec (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct sockaddr_in6* udp_send_addr ; 
 struct sockaddr_in6* udp_send_addr6 ; 
 scalar_t__ udp_send_iovec ; 
 struct our_mmsghdr* udp_send_msgvec ; 

int prepare_write_chain (struct udp_message *m, int max_messages) {
  int iovec_ptr = 0, msgvec_ptr = 0;
  struct our_mmsghdr *mm = udp_send_msgvec;

  while (m && msgvec_ptr < max_messages) {
    int res = rwm_prepare_iovec (&m->raw, udp_send_iovec + iovec_ptr, MAX_UDP_SEND_BUFFERS - iovec_ptr, MAX_UDP_SEND_DATAGRAM);
    if (res < 0) {
      break;
    }
    if (is_4in6 (m->ipv6)) {
      struct sockaddr_in *dest = mm->msg_hdr.msg_name = udp_send_addr + msgvec_ptr;
      dest->sin_family = AF_INET;
      dest->sin_port = htons (m->port);
      dest->sin_addr.s_addr = extract_4in6 (m->ipv6);
      mm->msg_hdr.msg_namelen = sizeof (struct sockaddr_in);
    } else {
      struct sockaddr_in6 *dest = mm->msg_hdr.msg_name = udp_send_addr6 + msgvec_ptr;
      dest->sin6_family = AF_INET6;
      dest->sin6_port = htons (m->port);
      memcpy (&dest->sin6_addr, m->ipv6, 16);
      mm->msg_hdr.msg_namelen = sizeof (struct sockaddr_in6);
    }
    mm->msg_hdr.msg_iov = udp_send_iovec + iovec_ptr;
    mm->msg_hdr.msg_iovlen = res;
    mm->msg_hdr.msg_flags = MSG_DONTWAIT;
    mm->msg_len = m->raw.total_bytes;

    int t = m->our_ip_idx;
    if (t > 0 && t < MAX_OUR_IPS && outbound_src_ip_hdr[t].msg_controllen) {
      mm->msg_hdr.msg_control = outbound_src_ip_hdr[t].msg_control;
      mm->msg_hdr.msg_controllen = outbound_src_ip_hdr[t].msg_controllen;
    } else {
      mm->msg_hdr.msg_control = 0;
      mm->msg_hdr.msg_controllen = 0;
    }

    iovec_ptr += res;
    ++msgvec_ptr;
    ++mm;
    m = m->next;
  }
  return msgvec_ptr;
}