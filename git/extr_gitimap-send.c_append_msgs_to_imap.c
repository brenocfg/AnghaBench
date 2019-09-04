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
struct strbuf {int dummy; } ;
struct imap_store {int /*<<< orphan*/  name; } ;
struct imap_server_conf {scalar_t__ use_html; int /*<<< orphan*/  folder; } ;

/* Variables and functions */
 int DRV_OK ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  imap_close_store (struct imap_store*) ; 
 struct imap_store* imap_open_store (struct imap_server_conf*,int /*<<< orphan*/ ) ; 
 int imap_store_msg (struct imap_store*,struct strbuf*) ; 
 int /*<<< orphan*/  split_msg (struct strbuf*,struct strbuf*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wrap_in_html (struct strbuf*) ; 

__attribute__((used)) static int append_msgs_to_imap(struct imap_server_conf *server,
			       struct strbuf* all_msgs, int total)
{
	struct strbuf msg = STRBUF_INIT;
	struct imap_store *ctx = NULL;
	int ofs = 0;
	int r;
	int n = 0;

	ctx = imap_open_store(server, server->folder);
	if (!ctx) {
		fprintf(stderr, "failed to open store\n");
		return 1;
	}
	ctx->name = server->folder;

	fprintf(stderr, "sending %d message%s\n", total, (total != 1) ? "s" : "");
	while (1) {
		unsigned percent = n * 100 / total;

		fprintf(stderr, "%4u%% (%d/%d) done\r", percent, n, total);

		if (!split_msg(all_msgs, &msg, &ofs))
			break;
		if (server->use_html)
			wrap_in_html(&msg);
		r = imap_store_msg(ctx, &msg);
		if (r != DRV_OK)
			break;
		n++;
	}
	fprintf(stderr, "\n");

	imap_close_store(ctx);

	return 0;
}