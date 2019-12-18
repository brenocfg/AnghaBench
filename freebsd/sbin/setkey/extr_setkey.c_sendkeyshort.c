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
typedef  int /*<<< orphan*/  u_int ;
struct sadb_msg {int /*<<< orphan*/  sadb_msg_pid; scalar_t__ sadb_msg_seq; scalar_t__ sadb_msg_reserved; int /*<<< orphan*/  sadb_msg_len; int /*<<< orphan*/  sadb_msg_satype; scalar_t__ sadb_msg_errno; int /*<<< orphan*/  sadb_msg_type; int /*<<< orphan*/  sadb_msg_version; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  PFKEY_UNIT64 (int) ; 
 int /*<<< orphan*/  PF_KEY_V2 ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  sendkeymsg (char*,int) ; 

void
sendkeyshort(u_int type, uint8_t satype)
{
	struct sadb_msg msg;

	msg.sadb_msg_version = PF_KEY_V2;
	msg.sadb_msg_type = type;
	msg.sadb_msg_errno = 0;
	msg.sadb_msg_satype = satype;
	msg.sadb_msg_len = PFKEY_UNIT64(sizeof(msg));
	msg.sadb_msg_reserved = 0;
	msg.sadb_msg_seq = 0;
	msg.sadb_msg_pid = getpid();

	sendkeymsg((char *)&msg, sizeof(msg));

	return;
}