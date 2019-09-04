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
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ GIT_MAX_HEXSZ ; 
 int find_unique_abbrev_r (scalar_t__,struct object_id const*,int) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,scalar_t__) ; 

void strbuf_add_unique_abbrev(struct strbuf *sb, const struct object_id *oid,
			      int abbrev_len)
{
	int r;
	strbuf_grow(sb, GIT_MAX_HEXSZ + 1);
	r = find_unique_abbrev_r(sb->buf + sb->len, oid, abbrev_len);
	strbuf_setlen(sb, sb->len + r);
}