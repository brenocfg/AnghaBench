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
 int /*<<< orphan*/  packet_trace (char*,int,int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char*,int) ; 

void packet_buf_delim(struct strbuf *buf)
{
	packet_trace("0001", 4, 1);
	strbuf_add(buf, "0001", 4);
}