#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct TYPE_7__ {scalar_t__ len; } ;
struct mailinfo {TYPE_1__ email; TYPE_1__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_sane_name (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_add (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  strbuf_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_trim (TYPE_1__*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void parse_bogus_from(struct mailinfo *mi, const struct strbuf *line)
{
	/* John Doe <johndoe> */

	char *bra, *ket;
	/* This is fallback, so do not bother if we already have an
	 * e-mail address.
	 */
	if (mi->email.len)
		return;

	bra = strchr(line->buf, '<');
	if (!bra)
		return;
	ket = strchr(bra, '>');
	if (!ket)
		return;

	strbuf_reset(&mi->email);
	strbuf_add(&mi->email, bra + 1, ket - bra - 1);

	strbuf_reset(&mi->name);
	strbuf_add(&mi->name, line->buf, bra - line->buf);
	strbuf_trim(&mi->name);
	get_sane_name(&mi->name, &mi->name, &mi->email);
}