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
struct ssh {TYPE_1__* kex; } ;
struct TYPE_2__ {int done; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int,int) ; 
 int /*<<< orphan*/  debug (char*,char*) ; 
 scalar_t__ do_debug ; 
 int do_send_and_receive (struct ssh*,struct ssh*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* ssh_err (int) ; 

__attribute__((used)) static void
run_kex(struct ssh *client, struct ssh *server)
{
	int r = 0;

	while (!server->kex->done || !client->kex->done) {
		if ((r = do_send_and_receive(server, client)) != 0) {
			debug("do_send_and_receive S2C: %s", ssh_err(r));
			break;
		}
		if ((r = do_send_and_receive(client, server)) != 0) {
			debug("do_send_and_receive C2S: %s", ssh_err(r));
			break;
		}
	}
	if (do_debug)
		printf("done: %s\n", ssh_err(r));
	ASSERT_INT_EQ(r, 0);
	ASSERT_INT_EQ(server->kex->done, 1);
	ASSERT_INT_EQ(client->kex->done, 1);
}