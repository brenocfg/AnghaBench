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
struct radius_session {int /*<<< orphan*/  username; } ;
struct eap_config {int dummy; } ;

/* Variables and functions */
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 char* os_strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  radius_server_testing_options_tls (struct radius_session*,char const*,struct eap_config*) ; 
 int /*<<< orphan*/  srv_log (struct radius_session*,char*,char const*) ; 

__attribute__((used)) static void radius_server_testing_options(struct radius_session *sess,
					  struct eap_config *eap_conf)
{
#ifdef CONFIG_TESTING_OPTIONS
	const char *pos;

	pos = os_strstr(sess->username, "@test-");
	if (pos == NULL)
		return;
	pos += 6;
	if (os_strncmp(pos, "tls-", 4) == 0)
		radius_server_testing_options_tls(sess, pos + 4, eap_conf);
	else
		srv_log(sess, "Unrecognized test: %s", pos);
#endif /* CONFIG_TESTING_OPTIONS */
}