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
typedef  int /*<<< orphan*/  va_list ;
struct xs_transaction {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_vprintf (struct sbuf*,char const*,int /*<<< orphan*/ ) ; 
 int xs_write (struct xs_transaction,char const*,char const*,int /*<<< orphan*/ ) ; 

int
xs_vprintf(struct xs_transaction t,
    const char *dir, const char *node, const char *fmt, va_list ap)
{
	struct sbuf *sb;
	int error;

	sb = sbuf_new_auto();
	sbuf_vprintf(sb, fmt, ap);
	sbuf_finish(sb);
	error = xs_write(t, dir, node, sbuf_data(sb));
	sbuf_delete(sb);

	return (error);
}