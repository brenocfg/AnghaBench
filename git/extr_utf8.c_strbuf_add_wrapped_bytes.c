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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strbuf_add_wrapped_text (struct strbuf*,char*,int,int,int) ; 
 char* xstrndup (char const*,int) ; 

void strbuf_add_wrapped_bytes(struct strbuf *buf, const char *data, int len,
			     int indent, int indent2, int width)
{
	char *tmp = xstrndup(data, len);
	strbuf_add_wrapped_text(buf, tmp, indent, indent2, width);
	free(tmp);
}