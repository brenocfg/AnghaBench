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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ strip_suffix_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static inline int strbuf_strip_suffix(struct strbuf *sb, const char *suffix)
{
	if (strip_suffix_mem(sb->buf, &sb->len, suffix)) {
		strbuf_setlen(sb, sb->len);
		return 1;
	} else
		return 0;
}