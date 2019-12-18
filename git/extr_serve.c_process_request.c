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
struct protocol_capability {int /*<<< orphan*/  (* command ) (int /*<<< orphan*/ ,struct argv_array*,struct packet_reader*) ;} ;
struct packet_reader {int options; int /*<<< orphan*/  line; } ;
struct argv_array {int /*<<< orphan*/  argc; } ;
typedef  enum request_state { ____Placeholder_request_state } request_state ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int PACKET_READ_CHOMP_NEWLINE ; 
#define  PACKET_READ_DELIM 131 
 int PACKET_READ_DIE_ON_ERR_PACKET ; 
#define  PACKET_READ_EOF 130 
#define  PACKET_READ_FLUSH 129 
 int PACKET_READ_GENTLE_ON_EOF ; 
#define  PACKET_READ_NORMAL 128 
 int PROCESS_REQUEST_DONE ; 
 int PROCESS_REQUEST_KEYS ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  is_command (int /*<<< orphan*/ ,struct protocol_capability**) ; 
 int /*<<< orphan*/  is_valid_capability (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_reader_init (struct packet_reader*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int packet_reader_peek (struct packet_reader*) ; 
 int /*<<< orphan*/  packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct argv_array*,struct packet_reader*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int process_request(void)
{
	enum request_state state = PROCESS_REQUEST_KEYS;
	struct packet_reader reader;
	struct argv_array keys = ARGV_ARRAY_INIT;
	struct protocol_capability *command = NULL;

	packet_reader_init(&reader, 0, NULL, 0,
			   PACKET_READ_CHOMP_NEWLINE |
			   PACKET_READ_GENTLE_ON_EOF |
			   PACKET_READ_DIE_ON_ERR_PACKET);

	/*
	 * Check to see if the client closed their end before sending another
	 * request.  If so we can terminate the connection.
	 */
	if (packet_reader_peek(&reader) == PACKET_READ_EOF)
		return 1;
	reader.options &= ~PACKET_READ_GENTLE_ON_EOF;

	while (state != PROCESS_REQUEST_DONE) {
		switch (packet_reader_peek(&reader)) {
		case PACKET_READ_EOF:
			BUG("Should have already died when seeing EOF");
		case PACKET_READ_NORMAL:
			/* collect request; a sequence of keys and values */
			if (is_command(reader.line, &command) ||
			    is_valid_capability(reader.line))
				argv_array_push(&keys, reader.line);
			else
				die("unknown capability '%s'", reader.line);

			/* Consume the peeked line */
			packet_reader_read(&reader);
			break;
		case PACKET_READ_FLUSH:
			/*
			 * If no command and no keys were given then the client
			 * wanted to terminate the connection.
			 */
			if (!keys.argc)
				return 1;

			/*
			 * The flush packet isn't consume here like it is in
			 * the other parts of this switch statement.  This is
			 * so that the command can read the flush packet and
			 * see the end of the request in the same way it would
			 * if command specific arguments were provided after a
			 * delim packet.
			 */
			state = PROCESS_REQUEST_DONE;
			break;
		case PACKET_READ_DELIM:
			/* Consume the peeked line */
			packet_reader_read(&reader);

			state = PROCESS_REQUEST_DONE;
			break;
		}
	}

	if (!command)
		die("no command requested");

	command->command(the_repository, &keys, &reader);

	argv_array_clear(&keys);
	return 0;
}