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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf const*) ; 
 size_t wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static void write_global_bin(FILE *f, const char *field,
			     const struct wpabuf *val)
{
	size_t i;
	const u8 *pos;

	if (val == NULL)
		return;

	fprintf(f, "%s=", field);
	pos = wpabuf_head(val);
	for (i = 0; i < wpabuf_len(val); i++)
		fprintf(f, "%02X", *pos++);
	fprintf(f, "\n");
}