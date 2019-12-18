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
struct sctp_paramhdr {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ sctp_m_getptr (struct mbuf*,int,int,int /*<<< orphan*/ *) ; 

struct sctp_paramhdr *
sctp_get_next_param(struct mbuf *m,
    int offset,
    struct sctp_paramhdr *pull,
    int pull_limit)
{
	/* This just provides a typed signature to Peter's Pull routine */
	return ((struct sctp_paramhdr *)sctp_m_getptr(m, offset, pull_limit,
	    (uint8_t *)pull));
}