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
struct rpc_service {int enabled; int /*<<< orphan*/  config_name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rpc_service*) ; 
 struct strbuf STRBUF_INIT ; 
 int getanyfile ; 
 int /*<<< orphan*/  git_config_get_bool (char*,int*) ; 
 int /*<<< orphan*/  git_config_get_ulong (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max_request_buffer ; 
 struct rpc_service* rpc_service ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void http_config(void)
{
	int i, value = 0;
	struct strbuf var = STRBUF_INIT;

	git_config_get_bool("http.getanyfile", &getanyfile);
	git_config_get_ulong("http.maxrequestbuffer", &max_request_buffer);

	for (i = 0; i < ARRAY_SIZE(rpc_service); i++) {
		struct rpc_service *svc = &rpc_service[i];
		strbuf_addf(&var, "http.%s", svc->config_name);
		if (!git_config_get_bool(var.buf, &value))
			svc->enabled = value;
		strbuf_reset(&var);
	}

	strbuf_release(&var);
}