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
struct sctp_pcb {int /*<<< orphan*/  random_counter; scalar_t__ random_store; scalar_t__ random_numbers; scalar_t__ store_at; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_HMAC ; 
 int /*<<< orphan*/  sctp_hmac (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void
sctp_fill_random_store(struct sctp_pcb *m)
{
	/*
	 * Here we use the MD5/SHA-1 to hash with our good randomNumbers and
	 * our counter. The result becomes our good random numbers and we
	 * then setup to give these out. Note that we do no locking to
	 * protect this. This is ok, since if competing folks call this we
	 * will get more gobbled gook in the random store which is what we
	 * want. There is a danger that two guys will use the same random
	 * numbers, but thats ok too since that is random as well :->
	 */
	m->store_at = 0;
	(void)sctp_hmac(SCTP_HMAC, (uint8_t *)m->random_numbers,
	    sizeof(m->random_numbers), (uint8_t *)&m->random_counter,
	    sizeof(m->random_counter), (uint8_t *)m->random_store);
	m->random_counter++;
}