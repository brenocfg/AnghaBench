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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int raw_nr; int /*<<< orphan*/ * raw; } ;
struct TYPE_3__ {int raw_nr; int /*<<< orphan*/ * raw; } ;
struct remote {int url_nr; scalar_t__ origin; int /*<<< orphan*/  name; TYPE_2__ fetch; TYPE_1__ push; int /*<<< orphan*/ * url; } ;

/* Variables and functions */
 scalar_t__ REMOTE_BRANCHES ; 
 scalar_t__ REMOTE_REMOTES ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  git_config_set_multivar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int migrate_file(struct remote *remote)
{
	struct strbuf buf = STRBUF_INIT;
	int i;

	strbuf_addf(&buf, "remote.%s.url", remote->name);
	for (i = 0; i < remote->url_nr; i++)
		git_config_set_multivar(buf.buf, remote->url[i], "^$", 0);
	strbuf_reset(&buf);
	strbuf_addf(&buf, "remote.%s.push", remote->name);
	for (i = 0; i < remote->push.raw_nr; i++)
		git_config_set_multivar(buf.buf, remote->push.raw[i], "^$", 0);
	strbuf_reset(&buf);
	strbuf_addf(&buf, "remote.%s.fetch", remote->name);
	for (i = 0; i < remote->fetch.raw_nr; i++)
		git_config_set_multivar(buf.buf, remote->fetch.raw[i], "^$", 0);
	if (remote->origin == REMOTE_REMOTES)
		unlink_or_warn(git_path("remotes/%s", remote->name));
	else if (remote->origin == REMOTE_BRANCHES)
		unlink_or_warn(git_path("branches/%s", remote->name));
	strbuf_release(&buf);

	return 0;
}