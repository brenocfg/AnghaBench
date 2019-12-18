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

/* Variables and functions */
 scalar_t__ PACKET_READ_FLUSH ; 
 scalar_t__ PACKET_READ_NORMAL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  server_capabilities_v2 ; 

__attribute__((used)) static void process_capabilities_v2(struct packet_reader *reader)
{
	while (packet_reader_read(reader) == PACKET_READ_NORMAL)
		argv_array_push(&server_capabilities_v2, reader->line);

	if (reader->status != PACKET_READ_FLUSH)
		die(_("expected flush after capabilities"));
}