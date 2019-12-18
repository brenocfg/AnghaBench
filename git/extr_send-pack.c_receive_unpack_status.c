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
struct packet_reader {int /*<<< orphan*/  line; } ;

/* Variables and functions */
 scalar_t__ PACKET_READ_NORMAL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  skip_prefix (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int receive_unpack_status(struct packet_reader *reader)
{
	if (packet_reader_read(reader) != PACKET_READ_NORMAL)
		return error(_("unexpected flush packet while reading remote unpack status"));
	if (!skip_prefix(reader->line, "unpack ", &reader->line))
		return error(_("unable to parse remote unpack status: %s"), reader->line);
	if (strcmp(reader->line, "ok"))
		return error(_("remote unpack failed: %s"), reader->line);
	return 0;
}