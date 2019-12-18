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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ng_source_embed_cnt_info {int next_val; int max_val; int min_val; int /*<<< orphan*/  flags; scalar_t__ width; int /*<<< orphan*/  offset; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  sc_p ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  ng_source_packet_mod (int /*<<< orphan*/ ,struct mbuf*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_source_mod_counter(sc_p sc, struct ng_source_embed_cnt_info *cnt,
    struct mbuf *m, int increment)
{
	caddr_t cp;
	uint32_t val;

	val = htonl(cnt->next_val);
	cp = (caddr_t)&val + sizeof(val) - cnt->width;
	ng_source_packet_mod(sc, m, cnt->offset, cnt->width, cp, cnt->flags);

	if (increment) {
		cnt->next_val += increment;

		if (increment > 0 && cnt->next_val > cnt->max_val) {
			cnt->next_val = cnt->min_val - 1 +
			    (cnt->next_val - cnt->max_val);
			if (cnt->next_val > cnt->max_val)
				cnt->next_val = cnt->max_val;
		} else if (increment < 0 && cnt->next_val < cnt->min_val) {
			cnt->next_val = cnt->max_val + 1 +
			    (cnt->next_val - cnt->min_val);
			if (cnt->next_val < cnt->min_val)
				cnt->next_val = cnt->max_val;
		}
	}
}