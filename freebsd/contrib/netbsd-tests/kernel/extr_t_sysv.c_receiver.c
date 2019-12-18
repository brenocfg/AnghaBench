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
struct testmsg {char* mtext; int /*<<< orphan*/  mtype; } ;

/* Variables and functions */
 scalar_t__ MESSAGE_TEXT_LEN ; 
 int /*<<< orphan*/  MTYPE_1 ; 
 int /*<<< orphan*/  MTYPE_1_ACK ; 
 int /*<<< orphan*/  MTYPE_2 ; 
 int /*<<< orphan*/  MTYPE_2_ACK ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m1_str ; 
 int /*<<< orphan*/  m2_str ; 
 int maxloop ; 
 int msgget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgkey ; 
 scalar_t__ msgrcv (int,struct testmsg*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msgsnd (int,struct testmsg*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void
receiver(void)
{
	struct testmsg m;
	int msqid, loop;

	if ((msqid = msgget(msgkey, 0)) == -1)
		err(1, "receiver: msgget");

	for (loop = 0; loop < maxloop; loop++) {
		/*
		 * Receive the first message, print it, and send an ACK.
		 */
		if (msgrcv(msqid, &m, MESSAGE_TEXT_LEN, MTYPE_1, 0) != MESSAGE_TEXT_LEN)
			err(1, "receiver: msgrcv 1");

		printf("%s\n", m.mtext);
		if (strcmp(m.mtext, m1_str) != 0)
			err(1, "receiver: message 1 data isn't correct");

		m.mtype = MTYPE_1_ACK;

		if (msgsnd(msqid, &m, MESSAGE_TEXT_LEN, 0) == -1)
			err(1, "receiver: msgsnd ack 1");

		/*
		 * Receive the second message, print it, and send an ACK.
		 */

		if (msgrcv(msqid, &m, MESSAGE_TEXT_LEN, MTYPE_2, 0) != MESSAGE_TEXT_LEN)
			err(1, "receiver: msgrcv 2");

		printf("%s\n", m.mtext);
		if (strcmp(m.mtext, m2_str) != 0)
			err(1, "receiver: message 2 data isn't correct");

		m.mtype = MTYPE_2_ACK;

		if (msgsnd(msqid, &m, MESSAGE_TEXT_LEN, 0) == -1)
			err(1, "receiver: msgsnd ack 2");
	}

	exit(0);
}