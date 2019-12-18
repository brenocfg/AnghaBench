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
struct TYPE_2__ {long tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,char*,...) ; 
 char* b64enc (char*) ; 
 int /*<<< orphan*/ * env_HTTP_PROXY ; 
 char* env_HTTP_PROXY_AUTH ; 
 char* env_HTTP_TIMEOUT ; 
 char* env_HTTP_USER_AGENT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* getenv (char*) ; 
 int /*<<< orphan*/ * proxyauth ; 
 char* proxyport ; 
 char* strchr (int /*<<< orphan*/ *,char) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 
 char* strsep (char**,char*) ; 
 long strtol (char*,char**,int) ; 
 TYPE_1__ timo ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static void
readenv(void)
{
	char *proxy_auth_userpass, *proxy_auth_userpass64, *p;
	char *proxy_auth_user = NULL;
	char *proxy_auth_pass = NULL;
	long http_timeout;

	env_HTTP_PROXY = getenv("HTTP_PROXY");
	if (env_HTTP_PROXY == NULL)
		env_HTTP_PROXY = getenv("http_proxy");
	if (env_HTTP_PROXY != NULL) {
		if (strncmp(env_HTTP_PROXY, "http://", 7) == 0)
			env_HTTP_PROXY += 7;
		p = strchr(env_HTTP_PROXY, '/');
		if (p != NULL)
			*p = 0;
		p = strchr(env_HTTP_PROXY, ':');
		if (p != NULL) {
			*p = 0;
			proxyport = p + 1;
		} else
			proxyport = "3128";
	}

	env_HTTP_PROXY_AUTH = getenv("HTTP_PROXY_AUTH");
	if ((env_HTTP_PROXY != NULL) &&
	    (env_HTTP_PROXY_AUTH != NULL) &&
	    (strncasecmp(env_HTTP_PROXY_AUTH, "basic:" , 6) == 0)) {
		/* Ignore authentication scheme */
		(void) strsep(&env_HTTP_PROXY_AUTH, ":");

		/* Ignore realm */
		(void) strsep(&env_HTTP_PROXY_AUTH, ":");

		/* Obtain username and password */
		proxy_auth_user = strsep(&env_HTTP_PROXY_AUTH, ":");
		proxy_auth_pass = env_HTTP_PROXY_AUTH;
	}

	if ((proxy_auth_user != NULL) && (proxy_auth_pass != NULL)) {
		asprintf(&proxy_auth_userpass, "%s:%s",
		    proxy_auth_user, proxy_auth_pass);
		if (proxy_auth_userpass == NULL)
			err(1, "asprintf");

		proxy_auth_userpass64 = b64enc(proxy_auth_userpass);
		if (proxy_auth_userpass64 == NULL)
			err(1, "malloc");

		asprintf(&proxyauth, "Proxy-Authorization: Basic %s\r\n",
		    proxy_auth_userpass64);
		if (proxyauth == NULL)
			err(1, "asprintf");

		free(proxy_auth_userpass);
		free(proxy_auth_userpass64);
	} else
		proxyauth = NULL;

	env_HTTP_USER_AGENT = getenv("HTTP_USER_AGENT");
	if (env_HTTP_USER_AGENT == NULL)
		env_HTTP_USER_AGENT = "phttpget/0.1";

	env_HTTP_TIMEOUT = getenv("HTTP_TIMEOUT");
	if (env_HTTP_TIMEOUT != NULL) {
		http_timeout = strtol(env_HTTP_TIMEOUT, &p, 10);
		if ((*env_HTTP_TIMEOUT == '\0') || (*p != '\0') ||
		    (http_timeout < 0))
			warnx("HTTP_TIMEOUT (%s) is not a positive integer",
			    env_HTTP_TIMEOUT);
		else
			timo.tv_sec = http_timeout;
	}
}