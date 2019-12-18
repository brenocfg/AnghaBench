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
typedef  int /*<<< orphan*/  uint8_t ;
struct lio_recv_pkt {int dummy; } ;
struct lio_recv_info {int /*<<< orphan*/ * rsvd; struct lio_recv_pkt* recv_pkt; } ;

/* Variables and functions */
 int LIO_RECV_INFO_SIZE ; 
 int LIO_RECV_PKT_SIZE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct lio_recv_info *
lio_alloc_recv_info(int extra_bytes)
{
	struct lio_recv_info	*recv_info;
	uint8_t			*buf;

	buf = malloc(LIO_RECV_PKT_SIZE + LIO_RECV_INFO_SIZE +
		     extra_bytes, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (buf == NULL)
		return (NULL);

	recv_info = (struct lio_recv_info *)buf;
	recv_info->recv_pkt = (struct lio_recv_pkt *)(buf + LIO_RECV_INFO_SIZE);
	recv_info->rsvd = NULL;
	if (extra_bytes)
		recv_info->rsvd = buf + LIO_RECV_INFO_SIZE + LIO_RECV_PKT_SIZE;

	return (recv_info);
}