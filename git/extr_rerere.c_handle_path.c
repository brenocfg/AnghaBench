#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct rerere_io {int /*<<< orphan*/  (* getline ) (struct strbuf*,struct rerere_io*) ;} ;
typedef  int /*<<< orphan*/  git_hash_ctx ;
struct TYPE_2__ {int /*<<< orphan*/  (* final_fn ) (unsigned char*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* init_fn ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int handle_conflict (struct strbuf*,struct rerere_io*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_cmarker (int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  rerere_io_putmem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rerere_io*) ; 
 int /*<<< orphan*/  rerere_io_putstr (int /*<<< orphan*/ ,struct rerere_io*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct strbuf*,struct rerere_io*) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static int handle_path(unsigned char *hash, struct rerere_io *io, int marker_size)
{
	git_hash_ctx ctx;
	struct strbuf buf = STRBUF_INIT, out = STRBUF_INIT;
	int has_conflicts = 0;
	if (hash)
		the_hash_algo->init_fn(&ctx);

	while (!io->getline(&buf, io)) {
		if (is_cmarker(buf.buf, '<', marker_size)) {
			has_conflicts = handle_conflict(&out, io, marker_size,
							hash ? &ctx : NULL);
			if (has_conflicts < 0)
				break;
			rerere_io_putmem(out.buf, out.len, io);
			strbuf_reset(&out);
		} else
			rerere_io_putstr(buf.buf, io);
	}
	strbuf_release(&buf);
	strbuf_release(&out);

	if (hash)
		the_hash_algo->final_fn(hash, &ctx);

	return has_conflicts;
}