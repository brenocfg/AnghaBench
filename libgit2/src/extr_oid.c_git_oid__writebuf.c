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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_buf_put (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/  const*) ; 

void git_oid__writebuf(git_buf *buf, const char *header, const git_oid *oid)
{
	char hex_oid[GIT_OID_HEXSZ];

	git_oid_fmt(hex_oid, oid);
	git_buf_puts(buf, header);
	git_buf_put(buf, hex_oid, GIT_OID_HEXSZ);
	git_buf_putc(buf, '\n');
}