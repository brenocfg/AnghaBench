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
struct image {int nr; TYPE_1__* line; } ;
struct apply_state {int dummy; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ match_fragment (struct apply_state*,struct image*,struct image*,struct image*,unsigned long,int,unsigned int,int,int) ; 

__attribute__((used)) static int find_pos(struct apply_state *state,
		    struct image *img,
		    struct image *preimage,
		    struct image *postimage,
		    int line,
		    unsigned ws_rule,
		    int match_beginning, int match_end)
{
	int i;
	unsigned long backwards, forwards, current;
	int backwards_lno, forwards_lno, current_lno;

	/*
	 * If match_beginning or match_end is specified, there is no
	 * point starting from a wrong line that will never match and
	 * wander around and wait for a match at the specified end.
	 */
	if (match_beginning)
		line = 0;
	else if (match_end)
		line = img->nr - preimage->nr;

	/*
	 * Because the comparison is unsigned, the following test
	 * will also take care of a negative line number that can
	 * result when match_end and preimage is larger than the target.
	 */
	if ((size_t) line > img->nr)
		line = img->nr;

	current = 0;
	for (i = 0; i < line; i++)
		current += img->line[i].len;

	/*
	 * There's probably some smart way to do this, but I'll leave
	 * that to the smart and beautiful people. I'm simple and stupid.
	 */
	backwards = current;
	backwards_lno = line;
	forwards = current;
	forwards_lno = line;
	current_lno = line;

	for (i = 0; ; i++) {
		if (match_fragment(state, img, preimage, postimage,
				   current, current_lno, ws_rule,
				   match_beginning, match_end))
			return current_lno;

	again:
		if (backwards_lno == 0 && forwards_lno == img->nr)
			break;

		if (i & 1) {
			if (backwards_lno == 0) {
				i++;
				goto again;
			}
			backwards_lno--;
			backwards -= img->line[backwards_lno].len;
			current = backwards;
			current_lno = backwards_lno;
		} else {
			if (forwards_lno == img->nr) {
				i++;
				goto again;
			}
			forwards += img->line[forwards_lno].len;
			forwards_lno++;
			current = forwards;
			current_lno = forwards_lno;
		}

	}
	return -1;
}