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
struct remote {int /*<<< orphan*/  name; } ;
struct branch {int /*<<< orphan*/  refname; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_detached_head_die ; 
 int /*<<< orphan*/  refspec_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_push_current(struct remote *remote, struct branch *branch)
{
	struct strbuf refspec = STRBUF_INIT;

	if (!branch)
		die(_(message_detached_head_die), remote->name);
	strbuf_addf(&refspec, "%s:%s", branch->refname, branch->refname);
	refspec_append(&rs, refspec.buf);
}