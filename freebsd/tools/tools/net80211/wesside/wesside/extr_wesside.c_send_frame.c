#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_3__ {int retries; int waiting_ack; TYPE_2__ tsent; int /*<<< orphan*/  psent; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int gettimeofday (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hexdump (unsigned char*,int) ; 
 int /*<<< orphan*/  inject (int,unsigned char*,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_print (char*,int) ; 
 TYPE_1__ txstate ; 

void send_frame(int tx, unsigned char* buf, int len) {
	static unsigned char* lame = 0;
	static int lamelen = 0;
	static int lastlen = 0;

	// retransmit!
	if (len == -1) {
		txstate.retries++;

		if (txstate.retries > 10) {
			time_print("ERROR Max retransmists for (%d bytes):\n", 
			       lastlen);
			hexdump(&lame[0], lastlen);
//			exit(1);
		}
		len = lastlen;
//		printf("Warning doing a retransmit...\n");
	}
	// normal tx
	else {
		assert(!txstate.waiting_ack);
	
		if (len > lamelen) {
			if (lame)
				free(lame);
		
			lame = (unsigned char*) malloc(len);
			if(!lame) {
				perror("malloc()");
				exit(1);
			}

			lamelen = len;
		}

		memcpy(lame, buf, len);
		txstate.retries = 0;
		lastlen = len;
	}	

	inject(tx, lame, len);

	txstate.waiting_ack = 1;
	txstate.psent++;
	if (gettimeofday(&txstate.tsent, NULL) == -1) {
		perror("gettimeofday()");
		exit(1);
	}

#if 0
	printf("Wrote frame at %lu.%lu\n", 
	       txstate.tsent.tv_sec, txstate.tsent.tv_usec);
#endif	       
}