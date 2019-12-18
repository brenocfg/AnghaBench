#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  push_cert; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_PACK_PUSH_CERT_ALWAYS ; 
 int /*<<< orphan*/  SEND_PACK_PUSH_CERT_IF_ASKED ; 
 int /*<<< orphan*/  SEND_PACK_PUSH_CERT_NEVER ; 
 TYPE_1__ args ; 
 int error (char*,char const*) ; 
 int /*<<< orphan*/  git_config_get_value (char*,char const**) ; 
 int git_default_config (char const*,char const*,void*) ; 
 int /*<<< orphan*/  git_gpg_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int git_parse_maybe_bool (char const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int send_pack_config(const char *k, const char *v, void *cb)
{
	git_gpg_config(k, v, NULL);

	if (!strcmp(k, "push.gpgsign")) {
		const char *value;
		if (!git_config_get_value("push.gpgsign", &value)) {
			switch (git_parse_maybe_bool(value)) {
			case 0:
				args.push_cert = SEND_PACK_PUSH_CERT_NEVER;
				break;
			case 1:
				args.push_cert = SEND_PACK_PUSH_CERT_ALWAYS;
				break;
			default:
				if (value && !strcasecmp(value, "if-asked"))
					args.push_cert = SEND_PACK_PUSH_CERT_IF_ASKED;
				else
					return error("Invalid value for '%s'", k);
			}
		}
	}
	return git_default_config(k, v, cb);
}