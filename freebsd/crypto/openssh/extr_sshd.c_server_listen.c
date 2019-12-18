#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_6__ {struct TYPE_6__* rdomain; int /*<<< orphan*/  addrs; } ;
struct TYPE_5__ {size_t num_listen_addrs; TYPE_2__* listen_addrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  freeaddrinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listen_on_addrs (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  num_listen_socks ; 
 TYPE_1__ options ; 

__attribute__((used)) static void
server_listen(void)
{
	u_int i;

	for (i = 0; i < options.num_listen_addrs; i++) {
		listen_on_addrs(&options.listen_addrs[i]);
		freeaddrinfo(options.listen_addrs[i].addrs);
		free(options.listen_addrs[i].rdomain);
		memset(&options.listen_addrs[i], 0,
		    sizeof(options.listen_addrs[i]));
	}
	free(options.listen_addrs);
	options.listen_addrs = NULL;
	options.num_listen_addrs = 0;

	if (!num_listen_socks)
		fatal("Cannot bind any address.");
}