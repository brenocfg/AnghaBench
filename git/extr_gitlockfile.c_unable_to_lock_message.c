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
 int EEXIST ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  absolute_path (char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 

void unable_to_lock_message(const char *path, int err, struct strbuf *buf)
{
	if (err == EEXIST) {
		strbuf_addf(buf, _("Unable to create '%s.lock': %s.\n\n"
		    "Another git process seems to be running in this repository, e.g.\n"
		    "an editor opened by 'git commit'. Please make sure all processes\n"
		    "are terminated then try again. If it still fails, a git process\n"
		    "may have crashed in this repository earlier:\n"
		    "remove the file manually to continue."),
			    absolute_path(path), strerror(err));
	} else
		strbuf_addf(buf, _("Unable to create '%s.lock': %s"),
			    absolute_path(path), strerror(err));
}