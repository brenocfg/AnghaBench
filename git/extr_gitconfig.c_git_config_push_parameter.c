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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DATA_ENVIRONMENT ; 
 struct strbuf STRBUF_INIT ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sq_quote_buf (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

void git_config_push_parameter(const char *text)
{
	struct strbuf env = STRBUF_INIT;
	const char *old = getenv(CONFIG_DATA_ENVIRONMENT);
	if (old && *old) {
		strbuf_addstr(&env, old);
		strbuf_addch(&env, ' ');
	}
	sq_quote_buf(&env, text);
	setenv(CONFIG_DATA_ENVIRONMENT, env.buf, 1);
	strbuf_release(&env);
}