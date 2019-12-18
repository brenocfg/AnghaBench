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
struct sockbuf {scalar_t__ sb_hiwat; scalar_t__ sb_mbcnt; scalar_t__ sb_mbmax; } ;
struct socket {struct sockbuf so_rcv; } ;

/* Variables and functions */
 scalar_t__ DNS_WAIT ; 
 int SU_ISCONNECTED ; 
 int SU_OK ; 
 scalar_t__ sbused (struct sockbuf*) ; 
 scalar_t__ skippacket (struct sockbuf*) ; 

__attribute__((used)) static int
sohasdns(struct socket *so, void *arg, int waitflag)
{
	struct sockbuf *sb = &so->so_rcv;

	/* If the socket is full, we're ready. */
	if (sbused(sb) >= sb->sb_hiwat || sb->sb_mbcnt >= sb->sb_mbmax)
		goto ready;

	/* Check to see if we have a request. */
	if (skippacket(sb) == DNS_WAIT)
		return (SU_OK);

ready:
	return (SU_ISCONNECTED);
}