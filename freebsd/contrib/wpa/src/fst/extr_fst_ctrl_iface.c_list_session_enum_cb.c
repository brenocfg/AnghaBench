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
struct list_sessions_cb_ctx {int buf; int buflen; int reply_len; } ;
struct fst_session {int dummy; } ;
struct fst_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fst_session_get_id (struct fst_session*) ; 
 int os_snprintf (int,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void list_session_enum_cb(struct fst_group *g, struct fst_session *s,
				 void *ctx)
{
	struct list_sessions_cb_ctx *c = ctx;
	int ret;

	ret = os_snprintf(c->buf, c->buflen, " %u", fst_session_get_id(s));

	c->buf += ret;
	c->buflen -= ret;
	c->reply_len += ret;
}