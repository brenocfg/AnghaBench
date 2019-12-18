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
struct strbuf {int len; char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char const) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 

__attribute__((used)) static void sanitize_client(struct strbuf *out, const char *in)
{
	for (; *in; in++) {
		if (*in == '/')
			continue;
		if (*in == '.' && (!out->len || out->buf[out->len - 1] == '.'))
			continue;
		strbuf_addch(out, *in);
	}

	while (out->len && out->buf[out->len - 1] == '.')
		strbuf_setlen(out, out->len - 1);
}