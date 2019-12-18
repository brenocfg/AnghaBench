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
typedef  int u_char ;
struct sadb_msg {scalar_t__ sadb_msg_type; int sadb_msg_satype; int /*<<< orphan*/  sadb_msg_len; int /*<<< orphan*/  sadb_msg_pid; scalar_t__ sadb_msg_seq; scalar_t__ sadb_msg_reserved; scalar_t__ sadb_msg_errno; int /*<<< orphan*/  sadb_msg_version; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_PEEK ; 
 int /*<<< orphan*/  PFKEY_UNIT64 (int) ; 
 int PFKEY_UNUNIT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_KEY_V2 ; 
 scalar_t__ SADB_X_PROMISC ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ f_hexdump ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kdebug_sadb (struct sadb_msg*) ; 
 int /*<<< orphan*/  printdate () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int recv (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int send (int /*<<< orphan*/ ,struct sadb_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  so ; 
 int /*<<< orphan*/  stdout ; 

void
promisc()
{
	struct sadb_msg msg;
	u_char rbuf[1024 * 32];	/* XXX: Enough ? Should I do MSG_PEEK ? */
	ssize_t l;

	msg.sadb_msg_version = PF_KEY_V2;
	msg.sadb_msg_type = SADB_X_PROMISC;
	msg.sadb_msg_errno = 0;
	msg.sadb_msg_satype = 1;
	msg.sadb_msg_len = PFKEY_UNIT64(sizeof(msg));
	msg.sadb_msg_reserved = 0;
	msg.sadb_msg_seq = 0;
	msg.sadb_msg_pid = getpid();

	if ((l = send(so, &msg, sizeof(msg), 0)) < 0) {
		err(1, "send");
		/*NOTREACHED*/
	}

	while (1) {
		struct sadb_msg *base;

		if ((l = recv(so, rbuf, sizeof(*base), MSG_PEEK)) < 0) {
			err(1, "recv");
			/*NOTREACHED*/
		}

		if (l != sizeof(*base))
			continue;

		base = (struct sadb_msg *)rbuf;
		if ((l = recv(so, rbuf, PFKEY_UNUNIT64(base->sadb_msg_len),
				0)) < 0) {
			err(1, "recv");
			/*NOTREACHED*/
		}
		printdate();
		if (f_hexdump) {
			int i;
			for (i = 0; i < l; i++) {
				if (i % 16 == 0)
					printf("%08x: ", i);
				printf("%02x ", rbuf[i] & 0xff);
				if (i % 16 == 15)
					printf("\n");
			}
			if (l % 16)
				printf("\n");
		}
		/* adjust base pointer for promisc mode */
		if (base->sadb_msg_type == SADB_X_PROMISC) {
			if ((ssize_t)sizeof(*base) < l)
				base++;
			else
				base = NULL;
		}
		if (base) {
			kdebug_sadb(base);
			printf("\n");
			fflush(stdout);
		}
	}
}