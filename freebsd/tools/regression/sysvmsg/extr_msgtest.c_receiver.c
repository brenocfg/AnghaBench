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
struct test_mymsg {char* mtext; int /*<<< orphan*/  mtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTYPE_1 ; 
 int /*<<< orphan*/  MTYPE_1_ACK ; 
 int /*<<< orphan*/  MTYPE_2 ; 
 int /*<<< orphan*/  MTYPE_2_ACK ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m1_str ; 
 int /*<<< orphan*/  m2_str ; 
 int msgget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgkey ; 
 scalar_t__ msgrcv (int,struct test_mymsg*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msgsnd (int,struct test_mymsg*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void
receiver()
{
	struct test_mymsg m;
	int msqid;

	if ((msqid = msgget(msgkey, 0)) == -1)
		err(1, "receiver: msgget");

	/*
	 * Receive the first message, print it, and send an ACK.
	 */

	if (msgrcv(msqid, &m, sizeof(m.mtext), MTYPE_1, 0) !=
	    strlen(m1_str) + 1)
		err(1, "receiver: msgrcv 1");

	printf("%s\n", m.mtext);
	if (strcmp(m.mtext, m1_str) != 0)
		err(1, "receiver: message 1 data isn't correct");

	m.mtype = MTYPE_1_ACK;

	if (msgsnd(msqid, &m, strlen(m1_str) + 1, 0) == -1)
		err(1, "receiver: msgsnd ack 1");

	/*
	 * Receive the second message, print it, and send an ACK.
	 */

	if (msgrcv(msqid, &m, sizeof(m.mtext), MTYPE_2, 0) !=
	    strlen(m2_str) + 1)
		err(1, "receiver: msgrcv 2");

	printf("%s\n", m.mtext);
	if (strcmp(m.mtext, m2_str) != 0)
		err(1, "receiver: message 2 data isn't correct");

	m.mtype = MTYPE_2_ACK;

	if (msgsnd(msqid, &m, strlen(m2_str) + 1, 0) == -1)
		err(1, "receiver: msgsnd ack 2");

	exit(0);
}