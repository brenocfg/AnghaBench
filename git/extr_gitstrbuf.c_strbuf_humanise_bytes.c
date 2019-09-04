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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,unsigned int,...) ; 

void strbuf_humanise_bytes(struct strbuf *buf, off_t bytes)
{
	if (bytes > 1 << 30) {
		strbuf_addf(buf, "%u.%2.2u GiB",
			    (unsigned)(bytes >> 30),
			    (unsigned)(bytes & ((1 << 30) - 1)) / 10737419);
	} else if (bytes > 1 << 20) {
		unsigned x = bytes + 5243;  /* for rounding */
		strbuf_addf(buf, "%u.%2.2u MiB",
			    x >> 20, ((x & ((1 << 20) - 1)) * 100) >> 20);
	} else if (bytes > 1 << 10) {
		unsigned x = bytes + 5;  /* for rounding */
		strbuf_addf(buf, "%u.%2.2u KiB",
			    x >> 10, ((x & ((1 << 10) - 1)) * 100) >> 10);
	} else {
		strbuf_addf(buf, "%u bytes", (unsigned)bytes);
	}
}