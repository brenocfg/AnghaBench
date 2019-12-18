#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct TYPE_11__ {char* password; } ;
struct TYPE_10__ {char* protocol; } ;
struct TYPE_9__ {char* host; } ;
struct TYPE_8__ {char* name; char* curl_deleg_param; char* ssl_version; } ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 char* CURLAUTH_ANY ; 
 int /*<<< orphan*/  CURLOPT_CAINFO ; 
 int /*<<< orphan*/  CURLOPT_CAPATH ; 
 int /*<<< orphan*/  CURLOPT_FTP_USE_EPSV ; 
 int /*<<< orphan*/  CURLOPT_GSSAPI_DELEGATION ; 
 int /*<<< orphan*/  CURLOPT_HTTPAUTH ; 
 int /*<<< orphan*/  CURLOPT_HTTP_VERSION ; 
 int /*<<< orphan*/  CURLOPT_KEYPASSWD ; 
 int /*<<< orphan*/  CURLOPT_LOW_SPEED_LIMIT ; 
 int /*<<< orphan*/  CURLOPT_LOW_SPEED_TIME ; 
 int /*<<< orphan*/  CURLOPT_MAXREDIRS ; 
 int /*<<< orphan*/  CURLOPT_NETRC ; 
 int /*<<< orphan*/  CURLOPT_NOPROXY ; 
 int /*<<< orphan*/  CURLOPT_PINNEDPUBLICKEY ; 
 int /*<<< orphan*/  CURLOPT_POST301 ; 
 int /*<<< orphan*/  CURLOPT_POSTREDIR ; 
 int /*<<< orphan*/  CURLOPT_PROTOCOLS ; 
 int /*<<< orphan*/  CURLOPT_PROXY ; 
 int /*<<< orphan*/  CURLOPT_PROXYTYPE ; 
 int /*<<< orphan*/  CURLOPT_PROXY_CAINFO ; 
 int /*<<< orphan*/  CURLOPT_REDIR_PROTOCOLS ; 
 int /*<<< orphan*/  CURLOPT_SSLCERT ; 
 int /*<<< orphan*/  CURLOPT_SSLKEY ; 
 int /*<<< orphan*/  CURLOPT_SSLVERSION ; 
 int /*<<< orphan*/  CURLOPT_SSL_CIPHER_LIST ; 
 int /*<<< orphan*/  CURLOPT_SSL_OPTIONS ; 
 int /*<<< orphan*/  CURLOPT_SSL_VERIFYHOST ; 
 int /*<<< orphan*/  CURLOPT_SSL_VERIFYPEER ; 
 int /*<<< orphan*/  CURLOPT_USERAGENT ; 
 int /*<<< orphan*/  CURLOPT_USE_SSL ; 
 int /*<<< orphan*/  CURLOPT_VERBOSE ; 
 char* CURLPROXY_HTTPS ; 
 char* CURLPROXY_SOCKS4 ; 
 char* CURLPROXY_SOCKS4A ; 
 char* CURLPROXY_SOCKS5 ; 
 char* CURLPROXY_SOCKS5_HOSTNAME ; 
 char* CURLSSLOPT_NO_REVOKE ; 
 char* CURLUSESSL_TRY ; 
 char* CURL_NETRC_OPTIONAL ; 
 char* CURL_REDIR_POST_ALL ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_6__ cert_auth ; 
 int /*<<< orphan*/  cookies_to_redact ; 
 int /*<<< orphan*/  credential_from_url (TYPE_2__*,char*) ; 
 char* curl_deleg ; 
 TYPE_1__* curl_deleg_levels ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 scalar_t__ curl_ftp_no_epsv ; 
 char* curl_http_proxy ; 
 scalar_t__ curl_http_version ; 
 char* curl_low_speed_limit ; 
 char* curl_low_speed_time ; 
 char* curl_no_proxy ; 
 scalar_t__ curl_ssl_try ; 
 int /*<<< orphan*/  curl_ssl_verify ; 
 int /*<<< orphan*/  die (char*,...) ; 
 char* get_curl_allowed_protocols (int) ; 
 int /*<<< orphan*/  get_curl_http_version_opt (scalar_t__,long*) ; 
 char* getenv (char*) ; 
 int git_user_agent () ; 
 scalar_t__ has_cert_password () ; 
 TYPE_3__ http_auth ; 
 scalar_t__ http_proactive_auth ; 
 int /*<<< orphan*/  http_schannel_check_revoke ; 
 int /*<<< orphan*/  http_schannel_use_ssl_cainfo ; 
 char* http_ssl_backend ; 
 int /*<<< orphan*/  init_curl_http_auth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_curl_proxy_auth (int /*<<< orphan*/ *) ; 
 TYPE_2__ proxy_auth ; 
 int /*<<< orphan*/  set_curl_keepalive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_curl_trace (int /*<<< orphan*/ *) ; 
 char* ssl_cainfo ; 
 char* ssl_capath ; 
 char* ssl_cert ; 
 char* ssl_cipherlist ; 
 char* ssl_key ; 
 char* ssl_pinnedkey ; 
 char* ssl_version ; 
 TYPE_1__* sslversions ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  string_list_sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_split (int /*<<< orphan*/ *,char*,char,int) ; 
 scalar_t__ strstr (char*,char*) ; 
 scalar_t__ trace_curl_data ; 
 int user_agent ; 
 int /*<<< orphan*/  var_override (char**,char*) ; 
 int /*<<< orphan*/  warning (char*,...) ; 

__attribute__((used)) static CURL *get_curl_handle(void)
{
	CURL *result = curl_easy_init();

	if (!result)
		die("curl_easy_init failed");

	if (!curl_ssl_verify) {
		curl_easy_setopt(result, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(result, CURLOPT_SSL_VERIFYHOST, 0);
	} else {
		/* Verify authenticity of the peer's certificate */
		curl_easy_setopt(result, CURLOPT_SSL_VERIFYPEER, 1);
		/* The name in the cert must match whom we tried to connect */
		curl_easy_setopt(result, CURLOPT_SSL_VERIFYHOST, 2);
	}

#if LIBCURL_VERSION_NUM >= 0x072f00 // 7.47.0
    if (curl_http_version) {
		long opt;
		if (!get_curl_http_version_opt(curl_http_version, &opt)) {
			/* Set request use http version */
			curl_easy_setopt(result, CURLOPT_HTTP_VERSION, opt);
		}
    }
#endif

#if LIBCURL_VERSION_NUM >= 0x070907
	curl_easy_setopt(result, CURLOPT_NETRC, CURL_NETRC_OPTIONAL);
#endif
#ifdef LIBCURL_CAN_HANDLE_AUTH_ANY
	curl_easy_setopt(result, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
#endif

#ifdef CURLGSSAPI_DELEGATION_FLAG
	if (curl_deleg) {
		int i;
		for (i = 0; i < ARRAY_SIZE(curl_deleg_levels); i++) {
			if (!strcmp(curl_deleg, curl_deleg_levels[i].name)) {
				curl_easy_setopt(result, CURLOPT_GSSAPI_DELEGATION,
						curl_deleg_levels[i].curl_deleg_param);
				break;
			}
		}
		if (i == ARRAY_SIZE(curl_deleg_levels))
			warning("Unknown delegation method '%s': using default",
				curl_deleg);
	}
#endif

	if (http_ssl_backend && !strcmp("schannel", http_ssl_backend) &&
	    !http_schannel_check_revoke) {
#if LIBCURL_VERSION_NUM >= 0x072c00
		curl_easy_setopt(result, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NO_REVOKE);
#else
		warning(_("CURLSSLOPT_NO_REVOKE not supported with cURL < 7.44.0"));
#endif
	}

	if (http_proactive_auth)
		init_curl_http_auth(result);

	if (getenv("GIT_SSL_VERSION"))
		ssl_version = getenv("GIT_SSL_VERSION");
	if (ssl_version && *ssl_version) {
		int i;
		for (i = 0; i < ARRAY_SIZE(sslversions); i++) {
			if (!strcmp(ssl_version, sslversions[i].name)) {
				curl_easy_setopt(result, CURLOPT_SSLVERSION,
						 sslversions[i].ssl_version);
				break;
			}
		}
		if (i == ARRAY_SIZE(sslversions))
			warning("unsupported ssl version %s: using default",
				ssl_version);
	}

	if (getenv("GIT_SSL_CIPHER_LIST"))
		ssl_cipherlist = getenv("GIT_SSL_CIPHER_LIST");
	if (ssl_cipherlist != NULL && *ssl_cipherlist)
		curl_easy_setopt(result, CURLOPT_SSL_CIPHER_LIST,
				ssl_cipherlist);

	if (ssl_cert != NULL)
		curl_easy_setopt(result, CURLOPT_SSLCERT, ssl_cert);
	if (has_cert_password())
		curl_easy_setopt(result, CURLOPT_KEYPASSWD, cert_auth.password);
#if LIBCURL_VERSION_NUM >= 0x070903
	if (ssl_key != NULL)
		curl_easy_setopt(result, CURLOPT_SSLKEY, ssl_key);
#endif
#if LIBCURL_VERSION_NUM >= 0x070908
	if (ssl_capath != NULL)
		curl_easy_setopt(result, CURLOPT_CAPATH, ssl_capath);
#endif
#if LIBCURL_VERSION_NUM >= 0x072c00
	if (ssl_pinnedkey != NULL)
		curl_easy_setopt(result, CURLOPT_PINNEDPUBLICKEY, ssl_pinnedkey);
#endif
	if (http_ssl_backend && !strcmp("schannel", http_ssl_backend) &&
	    !http_schannel_use_ssl_cainfo) {
		curl_easy_setopt(result, CURLOPT_CAINFO, NULL);
#if LIBCURL_VERSION_NUM >= 0x073400
		curl_easy_setopt(result, CURLOPT_PROXY_CAINFO, NULL);
#endif
	} else if (ssl_cainfo != NULL)
		curl_easy_setopt(result, CURLOPT_CAINFO, ssl_cainfo);

	if (curl_low_speed_limit > 0 && curl_low_speed_time > 0) {
		curl_easy_setopt(result, CURLOPT_LOW_SPEED_LIMIT,
				 curl_low_speed_limit);
		curl_easy_setopt(result, CURLOPT_LOW_SPEED_TIME,
				 curl_low_speed_time);
	}

	curl_easy_setopt(result, CURLOPT_MAXREDIRS, 20);
#if LIBCURL_VERSION_NUM >= 0x071301
	curl_easy_setopt(result, CURLOPT_POSTREDIR, CURL_REDIR_POST_ALL);
#elif LIBCURL_VERSION_NUM >= 0x071101
	curl_easy_setopt(result, CURLOPT_POST301, 1);
#endif
#ifdef CURLPROTO_HTTP
	curl_easy_setopt(result, CURLOPT_REDIR_PROTOCOLS,
			 get_curl_allowed_protocols(0));
	curl_easy_setopt(result, CURLOPT_PROTOCOLS,
			 get_curl_allowed_protocols(-1));
#else
	warning(_("Protocol restrictions not supported with cURL < 7.19.4"));
#endif
	if (getenv("GIT_CURL_VERBOSE"))
		curl_easy_setopt(result, CURLOPT_VERBOSE, 1L);
	setup_curl_trace(result);
	if (getenv("GIT_TRACE_CURL_NO_DATA"))
		trace_curl_data = 0;
	if (getenv("GIT_REDACT_COOKIES")) {
		string_list_split(&cookies_to_redact,
				  getenv("GIT_REDACT_COOKIES"), ',', -1);
		string_list_sort(&cookies_to_redact);
	}

	curl_easy_setopt(result, CURLOPT_USERAGENT,
		user_agent ? user_agent : git_user_agent());

	if (curl_ftp_no_epsv)
		curl_easy_setopt(result, CURLOPT_FTP_USE_EPSV, 0);

#ifdef CURLOPT_USE_SSL
	if (curl_ssl_try)
		curl_easy_setopt(result, CURLOPT_USE_SSL, CURLUSESSL_TRY);
#endif

	/*
	 * CURL also examines these variables as a fallback; but we need to query
	 * them here in order to decide whether to prompt for missing password (cf.
	 * init_curl_proxy_auth()).
	 *
	 * Unlike many other common environment variables, these are historically
	 * lowercase only. It appears that CURL did not know this and implemented
	 * only uppercase variants, which was later corrected to take both - with
	 * the exception of http_proxy, which is lowercase only also in CURL. As
	 * the lowercase versions are the historical quasi-standard, they take
	 * precedence here, as in CURL.
	 */
	if (!curl_http_proxy) {
		if (http_auth.protocol && !strcmp(http_auth.protocol, "https")) {
			var_override(&curl_http_proxy, getenv("HTTPS_PROXY"));
			var_override(&curl_http_proxy, getenv("https_proxy"));
		} else {
			var_override(&curl_http_proxy, getenv("http_proxy"));
		}
		if (!curl_http_proxy) {
			var_override(&curl_http_proxy, getenv("ALL_PROXY"));
			var_override(&curl_http_proxy, getenv("all_proxy"));
		}
	}

	if (curl_http_proxy && curl_http_proxy[0] == '\0') {
		/*
		 * Handle case with the empty http.proxy value here to keep
		 * common code clean.
		 * NB: empty option disables proxying at all.
		 */
		curl_easy_setopt(result, CURLOPT_PROXY, "");
	} else if (curl_http_proxy) {
#if LIBCURL_VERSION_NUM >= 0x071800
		if (starts_with(curl_http_proxy, "socks5h"))
			curl_easy_setopt(result,
				CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5_HOSTNAME);
		else if (starts_with(curl_http_proxy, "socks5"))
			curl_easy_setopt(result,
				CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
		else if (starts_with(curl_http_proxy, "socks4a"))
			curl_easy_setopt(result,
				CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4A);
		else if (starts_with(curl_http_proxy, "socks"))
			curl_easy_setopt(result,
				CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
#endif
#if LIBCURL_VERSION_NUM >= 0x073400
		else if (starts_with(curl_http_proxy, "https"))
			curl_easy_setopt(result,
				CURLOPT_PROXYTYPE, CURLPROXY_HTTPS);
#endif
		if (strstr(curl_http_proxy, "://"))
			credential_from_url(&proxy_auth, curl_http_proxy);
		else {
			struct strbuf url = STRBUF_INIT;
			strbuf_addf(&url, "http://%s", curl_http_proxy);
			credential_from_url(&proxy_auth, url.buf);
			strbuf_release(&url);
		}

		if (!proxy_auth.host)
			die("Invalid proxy URL '%s'", curl_http_proxy);

		curl_easy_setopt(result, CURLOPT_PROXY, proxy_auth.host);
#if LIBCURL_VERSION_NUM >= 0x071304
		var_override(&curl_no_proxy, getenv("NO_PROXY"));
		var_override(&curl_no_proxy, getenv("no_proxy"));
		curl_easy_setopt(result, CURLOPT_NOPROXY, curl_no_proxy);
#endif
	}
	init_curl_proxy_auth(result);

	set_curl_keepalive(result);

	return result;
}