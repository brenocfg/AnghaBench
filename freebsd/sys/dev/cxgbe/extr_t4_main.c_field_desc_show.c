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
typedef  int uintmax_t ;
typedef  int uint64_t ;
struct sbuf {int dummy; } ;
struct field_desc {char* name; unsigned long long width; int start; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 int snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static void
field_desc_show(struct sbuf *sb, uint64_t v, const struct field_desc *f)
{
	char buf[32];
	int line_size = 0;

	while (f->name) {
		uint64_t mask = (1ULL << f->width) - 1;
		int len = snprintf(buf, sizeof(buf), "%s: %ju", f->name,
		    ((uintmax_t)v >> f->start) & mask);

		if (line_size + len >= 79) {
			line_size = 8;
			sbuf_printf(sb, "\n        ");
		}
		sbuf_printf(sb, "%s ", buf);
		line_size += len + 1;
		f++;
	}
	sbuf_printf(sb, "\n");
}