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
struct packet_reader {int pktlen; char const* line; } ;
struct object_id {int dummy; } ;
typedef  enum ack_type { ____Placeholder_ack_type } ack_type ;

/* Variables and functions */
 int ACK ; 
 int ACK_common ; 
 int ACK_continue ; 
 int ACK_ready ; 
 int NAK ; 
 scalar_t__ PACKET_READ_NORMAL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  parse_oid_hex (char const*,struct object_id*,char const**) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static enum ack_type get_ack(struct packet_reader *reader,
			     struct object_id *result_oid)
{
	int len;
	const char *arg;

	if (packet_reader_read(reader) != PACKET_READ_NORMAL)
		die(_("git fetch-pack: expected ACK/NAK, got a flush packet"));
	len = reader->pktlen;

	if (!strcmp(reader->line, "NAK"))
		return NAK;
	if (skip_prefix(reader->line, "ACK ", &arg)) {
		const char *p;
		if (!parse_oid_hex(arg, result_oid, &p)) {
			len -= p - reader->line;
			if (len < 1)
				return ACK;
			if (strstr(p, "continue"))
				return ACK_continue;
			if (strstr(p, "common"))
				return ACK_common;
			if (strstr(p, "ready"))
				return ACK_ready;
			return ACK;
		}
	}
	die(_("git fetch-pack: expected ACK/NAK, got '%s'"), reader->line);
}