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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct mailinfo {int /*<<< orphan*/  transfer_encoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  TE_BASE64 ; 
 int /*<<< orphan*/  TE_DONTCARE ; 
 int /*<<< orphan*/  TE_QP ; 
 scalar_t__ strcasestr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void handle_content_transfer_encoding(struct mailinfo *mi,
					     const struct strbuf *line)
{
	if (strcasestr(line->buf, "base64"))
		mi->transfer_encoding = TE_BASE64;
	else if (strcasestr(line->buf, "quoted-printable"))
		mi->transfer_encoding = TE_QP;
	else
		mi->transfer_encoding = TE_DONTCARE;
}