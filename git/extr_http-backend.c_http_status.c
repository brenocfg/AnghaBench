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
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,unsigned int,char const*) ; 

__attribute__((used)) static void http_status(struct strbuf *hdr, unsigned code, const char *msg)
{
	strbuf_addf(hdr, "Status: %u %s\r\n", code, msg);
}