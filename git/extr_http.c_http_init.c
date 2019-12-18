#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urlmatch_config {char* section; int /*<<< orphan*/  vars; int /*<<< orphan*/  url; int /*<<< orphan*/ * cb; int /*<<< orphan*/  cascade_fn; int /*<<< orphan*/  collect_fn; int /*<<< orphan*/ * key; int /*<<< orphan*/  member_0; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct remote {int /*<<< orphan*/  http_proxy_authmethod; scalar_t__ http_proxy; } ;
struct TYPE_3__ {scalar_t__ name; } ;
typedef  TYPE_1__ curl_ssl_backend ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
#define  CURLSSLSET_NO_BACKENDS 131 
#define  CURLSSLSET_OK 130 
#define  CURLSSLSET_TOO_LATE 129 
#define  CURLSSLSET_UNKNOWN_BACKEND 128 
 int /*<<< orphan*/  CURL_GLOBAL_ALL ; 
 int DEFAULT_MAX_REQUESTS ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  STRING_LIST_INIT_DUP ; 
 char* _ (char*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  credential_from_url (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  curl_default ; 
 int curl_ftp_no_epsv ; 
 scalar_t__ curl_global_init (int /*<<< orphan*/ ) ; 
 int curl_global_sslset (int,scalar_t__,TYPE_1__ const***) ; 
 int /*<<< orphan*/  curl_http_proxy ; 
 void* curl_low_speed_limit ; 
 void* curl_low_speed_time ; 
 int /*<<< orphan*/  curl_multi_init () ; 
 scalar_t__ curl_session_count ; 
 void* curl_slist_append (int /*<<< orphan*/ ,char*) ; 
 int curl_ssl_verify ; 
 int /*<<< orphan*/  curlm ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_curl_handle () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,struct urlmatch_config*) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  http_auth ; 
 int /*<<< orphan*/  http_copy_default_headers () ; 
 scalar_t__ http_is_verbose ; 
 int /*<<< orphan*/  http_options ; 
 int http_proactive_auth ; 
 int /*<<< orphan*/  http_proxy_authmethod ; 
 scalar_t__ http_ssl_backend ; 
 int max_requests ; 
 void* no_pragma_header ; 
 void* pragma_header ; 
 int /*<<< orphan*/  set_from_env (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ssl_cainfo ; 
 int /*<<< orphan*/  ssl_capath ; 
 int /*<<< orphan*/  ssl_cert ; 
 int ssl_cert_password_required ; 
 int /*<<< orphan*/  ssl_key ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,scalar_t__) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int) ; 
 char* url_normalize (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  urlmatch_config_entry ; 
 int /*<<< orphan*/  user_agent ; 
 int /*<<< orphan*/  var_override (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (scalar_t__) ; 

void http_init(struct remote *remote, const char *url, int proactive_auth)
{
	char *low_speed_limit;
	char *low_speed_time;
	char *normalized_url;
	struct urlmatch_config config = { STRING_LIST_INIT_DUP };

	config.section = "http";
	config.key = NULL;
	config.collect_fn = http_options;
	config.cascade_fn = git_default_config;
	config.cb = NULL;

	http_is_verbose = 0;
	normalized_url = url_normalize(url, &config.url);

	git_config(urlmatch_config_entry, &config);
	free(normalized_url);
	string_list_clear(&config.vars, 1);

#if LIBCURL_VERSION_NUM >= 0x073800
	if (http_ssl_backend) {
		const curl_ssl_backend **backends;
		struct strbuf buf = STRBUF_INIT;
		int i;

		switch (curl_global_sslset(-1, http_ssl_backend, &backends)) {
		case CURLSSLSET_UNKNOWN_BACKEND:
			strbuf_addf(&buf, _("Unsupported SSL backend '%s'. "
					    "Supported SSL backends:"),
					    http_ssl_backend);
			for (i = 0; backends[i]; i++)
				strbuf_addf(&buf, "\n\t%s", backends[i]->name);
			die("%s", buf.buf);
		case CURLSSLSET_NO_BACKENDS:
			die(_("Could not set SSL backend to '%s': "
			      "cURL was built without SSL backends"),
			    http_ssl_backend);
		case CURLSSLSET_TOO_LATE:
			die(_("Could not set SSL backend to '%s': already set"),
			    http_ssl_backend);
		case CURLSSLSET_OK:
			break; /* Okay! */
		}
	}
#endif

	if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK)
		die("curl_global_init failed");

	http_proactive_auth = proactive_auth;

	if (remote && remote->http_proxy)
		curl_http_proxy = xstrdup(remote->http_proxy);

	if (remote)
		var_override(&http_proxy_authmethod, remote->http_proxy_authmethod);

	pragma_header = curl_slist_append(http_copy_default_headers(),
		"Pragma: no-cache");
	no_pragma_header = curl_slist_append(http_copy_default_headers(),
		"Pragma:");

#ifdef USE_CURL_MULTI
	{
		char *http_max_requests = getenv("GIT_HTTP_MAX_REQUESTS");
		if (http_max_requests != NULL)
			max_requests = atoi(http_max_requests);
	}

	curlm = curl_multi_init();
	if (!curlm)
		die("curl_multi_init failed");
#endif

	if (getenv("GIT_SSL_NO_VERIFY"))
		curl_ssl_verify = 0;

	set_from_env(&ssl_cert, "GIT_SSL_CERT");
#if LIBCURL_VERSION_NUM >= 0x070903
	set_from_env(&ssl_key, "GIT_SSL_KEY");
#endif
#if LIBCURL_VERSION_NUM >= 0x070908
	set_from_env(&ssl_capath, "GIT_SSL_CAPATH");
#endif
	set_from_env(&ssl_cainfo, "GIT_SSL_CAINFO");

	set_from_env(&user_agent, "GIT_HTTP_USER_AGENT");

	low_speed_limit = getenv("GIT_HTTP_LOW_SPEED_LIMIT");
	if (low_speed_limit != NULL)
		curl_low_speed_limit = strtol(low_speed_limit, NULL, 10);
	low_speed_time = getenv("GIT_HTTP_LOW_SPEED_TIME");
	if (low_speed_time != NULL)
		curl_low_speed_time = strtol(low_speed_time, NULL, 10);

	if (curl_ssl_verify == -1)
		curl_ssl_verify = 1;

	curl_session_count = 0;
#ifdef USE_CURL_MULTI
	if (max_requests < 1)
		max_requests = DEFAULT_MAX_REQUESTS;
#endif

	if (getenv("GIT_CURL_FTP_NO_EPSV"))
		curl_ftp_no_epsv = 1;

	if (url) {
		credential_from_url(&http_auth, url);
		if (!ssl_cert_password_required &&
		    getenv("GIT_SSL_CERT_PASSWORD_PROTECTED") &&
		    starts_with(url, "https://"))
			ssl_cert_password_required = 1;
	}

#ifndef NO_CURL_EASY_DUPHANDLE
	curl_default = get_curl_handle();
#endif
}