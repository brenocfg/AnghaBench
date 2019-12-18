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

/* Variables and functions */
 int /*<<< orphan*/  HTTP_FOLLOW_ALWAYS ; 
 int /*<<< orphan*/  HTTP_FOLLOW_INITIAL ; 
 int /*<<< orphan*/  HTTP_FOLLOW_NONE ; 
 scalar_t__ LARGE_PACKET_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int config_error_nonbool (char const*) ; 
 int /*<<< orphan*/  curl_cookie_file ; 
 int /*<<< orphan*/  curl_deleg ; 
 int curl_empty_auth ; 
 int curl_ftp_no_epsv ; 
 int /*<<< orphan*/  curl_http_proxy ; 
 int /*<<< orphan*/  curl_http_version ; 
 long curl_low_speed_limit ; 
 long curl_low_speed_time ; 
 int curl_save_cookies ; 
 int /*<<< orphan*/ * curl_slist_append (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ *) ; 
 int curl_ssl_try ; 
 int curl_ssl_verify ; 
 int /*<<< orphan*/ * extra_http_headers ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int git_config_bool (char const*,char const*) ; 
 void* git_config_int (char const*,char const*) ; 
 int git_config_pathname (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ git_config_ssize_t (char const*,char const*) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int git_default_config (char const*,char const*,void*) ; 
 int /*<<< orphan*/  http_follow_config ; 
 scalar_t__ http_post_buffer ; 
 int /*<<< orphan*/  http_proxy_authmethod ; 
 int http_schannel_check_revoke ; 
 int http_schannel_use_ssl_cainfo ; 
 int /*<<< orphan*/  http_ssl_backend ; 
 void* max_requests ; 
 int min_curl_sessions ; 
 int /*<<< orphan*/  ssl_cainfo ; 
 int /*<<< orphan*/  ssl_capath ; 
 int /*<<< orphan*/  ssl_cert ; 
 int ssl_cert_password_required ; 
 int /*<<< orphan*/  ssl_cipherlist ; 
 int /*<<< orphan*/  ssl_key ; 
 int /*<<< orphan*/  ssl_pinnedkey ; 
 int /*<<< orphan*/  ssl_version ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  user_agent ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  xstrdup_or_null (char const*) ; 

__attribute__((used)) static int http_options(const char *var, const char *value, void *cb)
{
	if (!strcmp("http.version", var)) {
		return git_config_string(&curl_http_version, var, value);
	}
	if (!strcmp("http.sslverify", var)) {
		curl_ssl_verify = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp("http.sslcipherlist", var))
		return git_config_string(&ssl_cipherlist, var, value);
	if (!strcmp("http.sslversion", var))
		return git_config_string(&ssl_version, var, value);
	if (!strcmp("http.sslcert", var))
		return git_config_pathname(&ssl_cert, var, value);
#if LIBCURL_VERSION_NUM >= 0x070903
	if (!strcmp("http.sslkey", var))
		return git_config_pathname(&ssl_key, var, value);
#endif
#if LIBCURL_VERSION_NUM >= 0x070908
	if (!strcmp("http.sslcapath", var))
		return git_config_pathname(&ssl_capath, var, value);
#endif
	if (!strcmp("http.sslcainfo", var))
		return git_config_pathname(&ssl_cainfo, var, value);
	if (!strcmp("http.sslcertpasswordprotected", var)) {
		ssl_cert_password_required = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp("http.ssltry", var)) {
		curl_ssl_try = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp("http.sslbackend", var)) {
		free(http_ssl_backend);
		http_ssl_backend = xstrdup_or_null(value);
		return 0;
	}

	if (!strcmp("http.schannelcheckrevoke", var)) {
		http_schannel_check_revoke = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp("http.schannelusesslcainfo", var)) {
		http_schannel_use_ssl_cainfo = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp("http.minsessions", var)) {
		min_curl_sessions = git_config_int(var, value);
#ifndef USE_CURL_MULTI
		if (min_curl_sessions > 1)
			min_curl_sessions = 1;
#endif
		return 0;
	}
#ifdef USE_CURL_MULTI
	if (!strcmp("http.maxrequests", var)) {
		max_requests = git_config_int(var, value);
		return 0;
	}
#endif
	if (!strcmp("http.lowspeedlimit", var)) {
		curl_low_speed_limit = (long)git_config_int(var, value);
		return 0;
	}
	if (!strcmp("http.lowspeedtime", var)) {
		curl_low_speed_time = (long)git_config_int(var, value);
		return 0;
	}

	if (!strcmp("http.noepsv", var)) {
		curl_ftp_no_epsv = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp("http.proxy", var))
		return git_config_string(&curl_http_proxy, var, value);

	if (!strcmp("http.proxyauthmethod", var))
		return git_config_string(&http_proxy_authmethod, var, value);

	if (!strcmp("http.cookiefile", var))
		return git_config_pathname(&curl_cookie_file, var, value);
	if (!strcmp("http.savecookies", var)) {
		curl_save_cookies = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp("http.postbuffer", var)) {
		http_post_buffer = git_config_ssize_t(var, value);
		if (http_post_buffer < 0)
			warning(_("negative value for http.postbuffer; defaulting to %d"), LARGE_PACKET_MAX);
		if (http_post_buffer < LARGE_PACKET_MAX)
			http_post_buffer = LARGE_PACKET_MAX;
		return 0;
	}

	if (!strcmp("http.useragent", var))
		return git_config_string(&user_agent, var, value);

	if (!strcmp("http.emptyauth", var)) {
		if (value && !strcmp("auto", value))
			curl_empty_auth = -1;
		else
			curl_empty_auth = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp("http.delegation", var)) {
#ifdef CURLGSSAPI_DELEGATION_FLAG
		return git_config_string(&curl_deleg, var, value);
#else
		warning(_("Delegation control is not supported with cURL < 7.22.0"));
		return 0;
#endif
	}

	if (!strcmp("http.pinnedpubkey", var)) {
#if LIBCURL_VERSION_NUM >= 0x072c00
		return git_config_pathname(&ssl_pinnedkey, var, value);
#else
		warning(_("Public key pinning not supported with cURL < 7.44.0"));
		return 0;
#endif
	}

	if (!strcmp("http.extraheader", var)) {
		if (!value) {
			return config_error_nonbool(var);
		} else if (!*value) {
			curl_slist_free_all(extra_http_headers);
			extra_http_headers = NULL;
		} else {
			extra_http_headers =
				curl_slist_append(extra_http_headers, value);
		}
		return 0;
	}

	if (!strcmp("http.followredirects", var)) {
		if (value && !strcmp(value, "initial"))
			http_follow_config = HTTP_FOLLOW_INITIAL;
		else if (git_config_bool(var, value))
			http_follow_config = HTTP_FOLLOW_ALWAYS;
		else
			http_follow_config = HTTP_FOLLOW_NONE;
		return 0;
	}

	/* Fall back on the default ones */
	return git_default_config(var, value, cb);
}