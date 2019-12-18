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
struct rpc_service {char const* name; scalar_t__ enabled; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rpc_service*) ; 
 int /*<<< orphan*/  forbidden (struct strbuf*,char*,char const*) ; 
 char* getenv (char*) ; 
 struct rpc_service* rpc_service ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static struct rpc_service *select_service(struct strbuf *hdr, const char *name)
{
	const char *svc_name;
	struct rpc_service *svc = NULL;
	int i;

	if (!skip_prefix(name, "git-", &svc_name))
		forbidden(hdr, "Unsupported service: '%s'", name);

	for (i = 0; i < ARRAY_SIZE(rpc_service); i++) {
		struct rpc_service *s = &rpc_service[i];
		if (!strcmp(s->name, svc_name)) {
			svc = s;
			break;
		}
	}

	if (!svc)
		forbidden(hdr, "Unsupported service: '%s'", name);

	if (svc->enabled < 0) {
		const char *user = getenv("REMOTE_USER");
		svc->enabled = (user && *user) ? 1 : 0;
	}
	if (!svc->enabled)
		forbidden(hdr, "Service not enabled: '%s'", svc->name);
	return svc;
}