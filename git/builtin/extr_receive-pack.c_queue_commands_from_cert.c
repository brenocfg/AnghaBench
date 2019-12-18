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
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
struct command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,...) ; 
 char* memchr (char const*,char,int) ; 
 int parse_signature (char*,int /*<<< orphan*/ ) ; 
 struct command** queue_command (struct command**,char const*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void queue_commands_from_cert(struct command **tail,
				     struct strbuf *push_cert)
{
	const char *boc, *eoc;

	if (*tail)
		die("protocol error: got both push certificate and unsigned commands");

	boc = strstr(push_cert->buf, "\n\n");
	if (!boc)
		die("malformed push certificate %.*s", 100, push_cert->buf);
	else
		boc += 2;
	eoc = push_cert->buf + parse_signature(push_cert->buf, push_cert->len);

	while (boc < eoc) {
		const char *eol = memchr(boc, '\n', eoc - boc);
		tail = queue_command(tail, boc, eol ? eol - boc : eoc - boc);
		boc = eol ? eol + 1 : eoc;
	}
}