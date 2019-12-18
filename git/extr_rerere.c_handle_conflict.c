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
struct strbuf {char* buf; scalar_t__ len; } ;
struct rerere_io {int /*<<< orphan*/  (* getline ) (struct strbuf*,struct rerere_io*) ;} ;
typedef  int /*<<< orphan*/  git_hash_ctx ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,char*,scalar_t__) ;} ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ is_cmarker (char*,char,int) ; 
 int /*<<< orphan*/  rerere_strbuf_putconflict (struct strbuf*,char,int) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 scalar_t__ strbuf_cmp (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  stub1 (struct strbuf*,struct rerere_io*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static int handle_conflict(struct strbuf *out, struct rerere_io *io,
			   int marker_size, git_hash_ctx *ctx)
{
	enum {
		RR_SIDE_1 = 0, RR_SIDE_2, RR_ORIGINAL
	} hunk = RR_SIDE_1;
	struct strbuf one = STRBUF_INIT, two = STRBUF_INIT;
	struct strbuf buf = STRBUF_INIT, conflict = STRBUF_INIT;
	int has_conflicts = -1;

	while (!io->getline(&buf, io)) {
		if (is_cmarker(buf.buf, '<', marker_size)) {
			if (handle_conflict(&conflict, io, marker_size, NULL) < 0)
				break;
			if (hunk == RR_SIDE_1)
				strbuf_addbuf(&one, &conflict);
			else
				strbuf_addbuf(&two, &conflict);
			strbuf_release(&conflict);
		} else if (is_cmarker(buf.buf, '|', marker_size)) {
			if (hunk != RR_SIDE_1)
				break;
			hunk = RR_ORIGINAL;
		} else if (is_cmarker(buf.buf, '=', marker_size)) {
			if (hunk != RR_SIDE_1 && hunk != RR_ORIGINAL)
				break;
			hunk = RR_SIDE_2;
		} else if (is_cmarker(buf.buf, '>', marker_size)) {
			if (hunk != RR_SIDE_2)
				break;
			if (strbuf_cmp(&one, &two) > 0)
				strbuf_swap(&one, &two);
			has_conflicts = 1;
			rerere_strbuf_putconflict(out, '<', marker_size);
			strbuf_addbuf(out, &one);
			rerere_strbuf_putconflict(out, '=', marker_size);
			strbuf_addbuf(out, &two);
			rerere_strbuf_putconflict(out, '>', marker_size);
			if (ctx) {
				the_hash_algo->update_fn(ctx, one.buf ?
							 one.buf : "",
							 one.len + 1);
				the_hash_algo->update_fn(ctx, two.buf ?
							 two.buf : "",
							 two.len + 1);
			}
			break;
		} else if (hunk == RR_SIDE_1)
			strbuf_addbuf(&one, &buf);
		else if (hunk == RR_ORIGINAL)
			; /* discard */
		else if (hunk == RR_SIDE_2)
			strbuf_addbuf(&two, &buf);
	}
	strbuf_release(&one);
	strbuf_release(&two);
	strbuf_release(&buf);

	return has_conflicts;
}