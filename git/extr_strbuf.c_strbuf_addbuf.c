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
struct strbuf {scalar_t__ len; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,scalar_t__) ; 

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
	strbuf_grow(sb, sb2->len);
	memcpy(sb->buf + sb->len, sb2->buf, sb2->len);
	strbuf_setlen(sb, sb->len + sb2->len);
}