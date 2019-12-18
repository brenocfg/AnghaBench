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
typedef  int /*<<< orphan*/  uint64_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_humanise_bytes (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_humanise_rate (struct strbuf*,unsigned int) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void throughput_string(struct strbuf *buf, uint64_t total,
			      unsigned int rate)
{
	strbuf_reset(buf);
	strbuf_addstr(buf, ", ");
	strbuf_humanise_bytes(buf, total);
	strbuf_addstr(buf, " | ");
	strbuf_humanise_rate(buf, rate * 1024);
}