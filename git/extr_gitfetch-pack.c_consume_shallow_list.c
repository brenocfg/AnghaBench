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
struct packet_reader {scalar_t__ status; int /*<<< orphan*/  line; } ;
struct fetch_pack_args {scalar_t__ deepen; scalar_t__ stateless_rpc; } ;

/* Variables and functions */
 scalar_t__ PACKET_READ_FLUSH ; 
 scalar_t__ PACKET_READ_NORMAL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 scalar_t__ starts_with (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void consume_shallow_list(struct fetch_pack_args *args,
				 struct packet_reader *reader)
{
	if (args->stateless_rpc && args->deepen) {
		/* If we sent a depth we will get back "duplicate"
		 * shallow and unshallow commands every time there
		 * is a block of have lines exchanged.
		 */
		while (packet_reader_read(reader) == PACKET_READ_NORMAL) {
			if (starts_with(reader->line, "shallow "))
				continue;
			if (starts_with(reader->line, "unshallow "))
				continue;
			die(_("git fetch-pack: expected shallow list"));
		}
		if (reader->status != PACKET_READ_FLUSH)
			die(_("git fetch-pack: expected a flush packet after shallow list"));
	}
}