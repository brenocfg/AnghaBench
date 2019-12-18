#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct TYPE_4__ {int nr; TYPE_1__* items; } ;
struct repository_format {int version; TYPE_2__ unknown_extensions; } ;
struct TYPE_3__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int GIT_REPO_VERSION_READ ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 

int verify_repository_format(const struct repository_format *format,
			     struct strbuf *err)
{
	if (GIT_REPO_VERSION_READ < format->version) {
		strbuf_addf(err, _("Expected git repo version <= %d, found %d"),
			    GIT_REPO_VERSION_READ, format->version);
		return -1;
	}

	if (format->version >= 1 && format->unknown_extensions.nr) {
		int i;

		strbuf_addstr(err, _("unknown repository extensions found:"));

		for (i = 0; i < format->unknown_extensions.nr; i++)
			strbuf_addf(err, "\n\t%s",
				    format->unknown_extensions.items[i].string);
		return -1;
	}

	return 0;
}