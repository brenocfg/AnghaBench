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
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ packet_reader_peek (struct packet_reader*) ; 
 int /*<<< orphan*/  packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int process_section_header(struct packet_reader *reader,
				  const char *section, int peek)
{
	int ret;

	if (packet_reader_peek(reader) != PACKET_READ_NORMAL)
		die(_("error reading section header '%s'"), section);

	ret = !strcmp(reader->line, section);

	if (!peek) {
		if (!ret)
			die(_("expected '%s', received '%s'"),
			    section, reader->line);
		packet_reader_read(reader);
	}

	return ret;
}