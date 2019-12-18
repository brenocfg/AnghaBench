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
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char const*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char) ; 

struct sbuf *
xs_join(const char *dir, const char *name)
{
	struct sbuf *sb;

	sb = sbuf_new_auto();
	sbuf_cat(sb, dir);
	if (name[0] != '\0') {
		sbuf_putc(sb, '/');
		sbuf_cat(sb, name);
	}
	sbuf_finish(sb);

	return (sb);
}