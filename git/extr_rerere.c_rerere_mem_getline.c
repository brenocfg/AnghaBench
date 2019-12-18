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
struct strbuf {int dummy; } ;
struct TYPE_2__ {size_t len; char* buf; } ;
struct rerere_io_mem {TYPE_1__ input; } ;
struct rerere_io {int dummy; } ;

/* Variables and functions */
 char* memchr (char*,char,size_t) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char*,size_t) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_remove (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int rerere_mem_getline(struct strbuf *sb, struct rerere_io *io_)
{
	struct rerere_io_mem *io = (struct rerere_io_mem *)io_;
	char *ep;
	size_t len;

	strbuf_release(sb);
	if (!io->input.len)
		return -1;
	ep = memchr(io->input.buf, '\n', io->input.len);
	if (!ep)
		ep = io->input.buf + io->input.len;
	else if (*ep == '\n')
		ep++;
	len = ep - io->input.buf;
	strbuf_add(sb, io->input.buf, len);
	strbuf_remove(&io->input, 0, len);
	return 0;
}