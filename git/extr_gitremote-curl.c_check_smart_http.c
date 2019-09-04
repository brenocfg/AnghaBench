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
struct strbuf {char const* buf; } ;
struct packet_reader {char const* line; scalar_t__ pktlen; int /*<<< orphan*/  src_len; int /*<<< orphan*/  src_buffer; } ;
struct discovery {int proto_git; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int PACKET_READ_CHOMP_NEWLINE ; 
 int PACKET_READ_DIE_ON_ERR_PACKET ; 
 scalar_t__ PACKET_READ_NORMAL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  packet_reader_init (struct packet_reader*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ packet_reader_read (struct packet_reader*) ; 
 scalar_t__ skip_prefix (char const*,char const*,char const**) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void check_smart_http(struct discovery *d, const char *service,
			     struct strbuf *type)
{
	const char *p;
	struct packet_reader reader;

	/*
	 * If we don't see x-$service-advertisement, then it's not smart-http.
	 * But once we do, we commit to it and assume any other protocol
	 * violations are hard errors.
	 */
	if (!skip_prefix(type->buf, "application/x-", &p) ||
	    !skip_prefix(p, service, &p) ||
	    strcmp(p, "-advertisement"))
		return;

	packet_reader_init(&reader, -1, d->buf, d->len,
			   PACKET_READ_CHOMP_NEWLINE |
			   PACKET_READ_DIE_ON_ERR_PACKET);
	if (packet_reader_read(&reader) != PACKET_READ_NORMAL)
		die(_("invalid server response; expected service, got flush packet"));

	if (skip_prefix(reader.line, "# service=", &p) && !strcmp(p, service)) {
		/*
		 * The header can include additional metadata lines, up
		 * until a packet flush marker.  Ignore these now, but
		 * in the future we might start to scan them.
		 */
		for (;;) {
			packet_reader_read(&reader);
			if (reader.pktlen <= 0) {
				break;
			}
		}

		/*
		 * v0 smart http; callers expect us to soak up the
		 * service and header packets
		 */
		d->buf = reader.src_buffer;
		d->len = reader.src_len;
		d->proto_git = 1;

	} else if (!strcmp(reader.line, "version 2")) {
		/*
		 * v2 smart http; do not consume version packet, which will
		 * be handled elsewhere.
		 */
		d->proto_git = 1;

	} else {
		die(_("invalid server response; got '%s'"), reader.line);
	}
}