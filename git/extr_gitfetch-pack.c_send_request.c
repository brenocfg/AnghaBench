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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct fetch_pack_args {scalar_t__ stateless_rpc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LARGE_PACKET_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_flush (int) ; 
 int /*<<< orphan*/  send_sideband (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_in_full (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_request(struct fetch_pack_args *args,
			 int fd, struct strbuf *buf)
{
	if (args->stateless_rpc) {
		send_sideband(fd, -1, buf->buf, buf->len, LARGE_PACKET_MAX);
		packet_flush(fd);
	} else {
		if (write_in_full(fd, buf->buf, buf->len) < 0)
			die_errno(_("unable to write to remote"));
	}
}