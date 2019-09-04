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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int error_errno (char*) ; 
 scalar_t__ fwrite (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_strbuf(struct strbuf *sb, FILE *out)
{
	if (fwrite(sb->buf, 1, sb->len, out) == sb->len)	/* Success. */
		return 0;
	return error_errno("cannot write delta postimage");
}