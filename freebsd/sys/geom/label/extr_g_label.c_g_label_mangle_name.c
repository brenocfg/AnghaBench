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
typedef  char u_char ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  isprint (char const) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 scalar_t__ sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const) ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char const) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
g_label_mangle_name(char *label, size_t size)
{
	struct sbuf *sb;
	const u_char *c;

	sb = sbuf_new(NULL, NULL, size, SBUF_FIXEDLEN);
	for (c = label; *c != '\0'; c++) {
		if (!isprint(*c) || isspace(*c) || *c =='"' || *c == '%')
			sbuf_printf(sb, "%%%02X", *c);
		else
			sbuf_putc(sb, *c);
	}
	if (sbuf_finish(sb) != 0)
		label[0] = '\0';
	else
		strlcpy(label, sbuf_data(sb), size);
	sbuf_delete(sb);
}