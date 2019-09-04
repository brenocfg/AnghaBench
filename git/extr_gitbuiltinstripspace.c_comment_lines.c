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
 int /*<<< orphan*/  strbuf_add_commented_lines (struct strbuf*,char*,size_t) ; 
 char* strbuf_detach (struct strbuf*,size_t*) ; 

__attribute__((used)) static void comment_lines(struct strbuf *buf)
{
	char *msg;
	size_t len;

	msg = strbuf_detach(buf, &len);
	strbuf_add_commented_lines(buf, msg, len);
	free(msg);
}