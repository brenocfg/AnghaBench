#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct tftphdr {scalar_t__ th_opcode; int th_block; } ;
struct tftp_stats {int /*<<< orphan*/  tstop; int /*<<< orphan*/  rollovers; int /*<<< orphan*/  retries; scalar_t__ amount; int /*<<< orphan*/  blocks; } ;
struct TYPE_2__ {int /*<<< orphan*/ * o_request; } ;

/* Variables and functions */
 scalar_t__ ACK ; 
 int DEBUG_SIMPLE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int MAXPKTSIZE ; 
 size_t OPT_ROLLOVER ; 
 int RP_TIMEOUT ; 
 int atoi (int /*<<< orphan*/ *) ; 
 int debug ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int maxtimeouts ; 
 TYPE_1__* options ; 
 int read_file (char*,int) ; 
 int receive_packet (int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rp_strerror (int) ; 
 int segsize ; 
 int send_data (int,int,char*,int) ; 
 int /*<<< orphan*/  send_error (int,scalar_t__) ; 
 int /*<<< orphan*/  synchnet (int) ; 
 int /*<<< orphan*/  tftp_log (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  timeoutpacket ; 

void
tftp_send(int peer, uint16_t *block, struct tftp_stats *ts)
{
	struct tftphdr *rp;
	int size, n_data, n_ack, try;
	uint16_t oldblock;
	char sendbuffer[MAXPKTSIZE];
	char recvbuffer[MAXPKTSIZE];

	rp = (struct tftphdr *)recvbuffer;
	*block = 1;
	ts->amount = 0;
	do {
		if (debug&DEBUG_SIMPLE)
			tftp_log(LOG_DEBUG, "Sending block %d", *block);

		size = read_file(sendbuffer, segsize);
		if (size < 0) {
			tftp_log(LOG_ERR, "read_file returned %d", size);
			send_error(peer, errno + 100);
			goto abort;
		}

		for (try = 0; ; try++) {
			n_data = send_data(peer, *block, sendbuffer, size);
			if (n_data > 0) {
				if (try == maxtimeouts) {
					tftp_log(LOG_ERR,
					    "Cannot send DATA packet #%d, "
					    "giving up", *block);
					return;
				}
				tftp_log(LOG_ERR,
				    "Cannot send DATA packet #%d, trying again",
				    *block);
				continue;
			}

			n_ack = receive_packet(peer, recvbuffer,
			    MAXPKTSIZE, NULL, timeoutpacket);
			if (n_ack < 0) {
				if (n_ack == RP_TIMEOUT) {
					if (try == maxtimeouts) {
						tftp_log(LOG_ERR,
						    "Timeout #%d send ACK %d "
						    "giving up", try, *block);
						return;
					}
					tftp_log(LOG_WARNING,
					    "Timeout #%d on ACK %d",
					    try, *block);
					continue;
				}

				/* Either read failure or ERROR packet */
				if (debug&DEBUG_SIMPLE)
					tftp_log(LOG_ERR, "Aborting: %s",
					    rp_strerror(n_ack));
				goto abort;
			}
			if (rp->th_opcode == ACK) {
				ts->blocks++;
				if (rp->th_block == *block) {
					ts->amount += size;
					break;
				}

				/* Re-synchronize with the other side */
				(void) synchnet(peer);
				if (rp->th_block == (*block - 1)) {
					ts->retries++;
					continue;
				}
			}

		}
		oldblock = *block;
		(*block)++;
		if (oldblock > *block) {
			if (options[OPT_ROLLOVER].o_request == NULL) {
				/*
				 * "rollover" option not specified in
				 * tftp client.  Default to rolling block
				 * counter to 0.
				 */
				*block = 0;
			} else {
				*block = atoi(options[OPT_ROLLOVER].o_request);
			}

			ts->rollovers++;
		}
		gettimeofday(&(ts->tstop), NULL);
	} while (size == segsize);
abort:
	return;
}