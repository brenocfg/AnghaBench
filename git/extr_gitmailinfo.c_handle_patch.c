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
struct mailinfo {int /*<<< orphan*/  patch_lines; int /*<<< orphan*/  patchfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_patch(struct mailinfo *mi, const struct strbuf *line)
{
	fwrite(line->buf, 1, line->len, mi->patchfile);
	mi->patch_lines++;
}