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
struct strbuf {char* buf; } ;
struct json_writer {struct strbuf json; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,double) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void fmt_double(struct json_writer *jw, int precision,
			      double value)
{
	if (precision < 0) {
		strbuf_addf(&jw->json, "%f", value);
	} else {
		struct strbuf fmt = STRBUF_INIT;
		strbuf_addf(&fmt, "%%.%df", precision);
		strbuf_addf(&jw->json, fmt.buf, value);
		strbuf_release(&fmt);
	}
}