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
struct params {int packet_try; int /*<<< orphan*/  plast; int /*<<< orphan*/  packet_len; int /*<<< orphan*/  packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  send_frame (struct params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int retransmit(struct params *p)
{
#if 0
	printf("RETRANS %d\n", p->packet_try);
#endif

	send_frame(p, p->packet, p->packet_len);
	p->packet_try++;

	if (p->packet_try > 3)
		p->packet_try = 0;
	else {
		if (gettimeofday(&p->plast, NULL) == -1)
			err(1, "gettimeofday()");
	}

	return p->packet_try;
}