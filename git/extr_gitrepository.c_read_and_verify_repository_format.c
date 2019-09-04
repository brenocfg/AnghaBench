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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository_format {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  read_repository_format (struct repository_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 scalar_t__ verify_repository_format (struct repository_format*,struct strbuf*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_and_verify_repository_format(struct repository_format *format,
					     const char *commondir)
{
	int ret = 0;
	struct strbuf sb = STRBUF_INIT;

	strbuf_addf(&sb, "%s/config", commondir);
	read_repository_format(format, sb.buf);
	strbuf_reset(&sb);

	if (verify_repository_format(format, &sb) < 0) {
		warning("%s", sb.buf);
		ret = -1;
	}

	strbuf_release(&sb);
	return ret;
}