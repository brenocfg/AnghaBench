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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (char**,int) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 char** order ; 
 int order_cnt ; 
 void* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 char* xmemdupz (char*,int) ; 

__attribute__((used)) static void prepare_order(const char *orderfile)
{
	int cnt, pass;
	struct strbuf sb = STRBUF_INIT;
	void *map;
	char *cp, *endp;
	ssize_t sz;

	if (order)
		return;

	sz = strbuf_read_file(&sb, orderfile, 0);
	if (sz < 0)
		die_errno(_("failed to read orderfile '%s'"), orderfile);
	map = strbuf_detach(&sb, NULL);
	endp = (char *) map + sz;

	for (pass = 0; pass < 2; pass++) {
		cnt = 0;
		cp = map;
		while (cp < endp) {
			char *ep;
			for (ep = cp; ep < endp && *ep != '\n'; ep++)
				;
			/* cp to ep has one line */
			if (*cp == '\n' || *cp == '#')
				; /* comment */
			else if (pass == 0)
				cnt++;
			else {
				if (*ep == '\n') {
					*ep = 0;
					order[cnt] = cp;
				} else {
					order[cnt] = xmemdupz(cp, ep - cp);
				}
				cnt++;
			}
			if (ep < endp)
				ep++;
			cp = ep;
		}
		if (pass == 0) {
			order_cnt = cnt;
			ALLOC_ARRAY(order, cnt);
		}
	}
}