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
typedef  int /*<<< orphan*/  uri ;
struct evkeyvalq {int dummy; } ;
struct evhttp_uri {int dummy; } ;
struct evhttp_request {int dummy; } ;
struct evhttp_connection {int dummy; } ;
struct evbuffer {int dummy; } ;
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BEV_OPT_CLOSE_ON_FREE ; 
 int BEV_OPT_DEFER_CALLBACKS ; 
 int /*<<< orphan*/  BUFFEREVENT_SSL_CONNECTING ; 
 int /*<<< orphan*/  CRYPTO_cleanup_all_ex_data () ; 
 int /*<<< orphan*/  ERR_free_strings () ; 
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 int /*<<< orphan*/  ERR_remove_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_remove_thread_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVHTTP_REQ_GET ; 
 int /*<<< orphan*/  EVHTTP_REQ_POST ; 
 int /*<<< orphan*/  EVP_cleanup () ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int RAND_poll () ; 
 int /*<<< orphan*/  SSL_COMP_get_compression_methods () ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int SSL_CTX_load_verify_locations (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_cert_verify_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_tlsext_host_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  SSLv23_method () ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  bufferevent_openssl_set_allow_dirty_shutdown (struct bufferevent*,int) ; 
 struct bufferevent* bufferevent_openssl_socket_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct bufferevent* bufferevent_socket_new (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cert_verify_callback ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  err_openssl (char*) ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char*,size_t) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_new () ; 
 int /*<<< orphan*/  evhttp_add_header (struct evkeyvalq*,char*,char const*) ; 
 struct evhttp_connection* evhttp_connection_base_bufferevent_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bufferevent*,char const*,int) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_set_retries (struct evhttp_connection*,int) ; 
 int /*<<< orphan*/  evhttp_connection_set_timeout (struct evhttp_connection*,int) ; 
 int evhttp_make_request (struct evhttp_connection*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 struct evbuffer* evhttp_request_get_output_buffer (struct evhttp_request*) ; 
 struct evkeyvalq* evhttp_request_get_output_headers (struct evhttp_request*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,struct bufferevent*) ; 
 int /*<<< orphan*/  evhttp_uri_free (struct evhttp_uri*) ; 
 char* evhttp_uri_get_host (struct evhttp_uri*) ; 
 char* evhttp_uri_get_path (struct evhttp_uri*) ; 
 int evhttp_uri_get_port (struct evhttp_uri*) ; 
 char* evhttp_uri_get_query (struct evhttp_uri*) ; 
 char* evhttp_uri_get_scheme (struct evhttp_uri*) ; 
 struct evhttp_uri* evhttp_uri_parse (char const*) ; 
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_request_done ; 
 int ignore_cert ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sk_SSL_COMP_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  syntax () ; 

int
main(int argc, char **argv)
{
	int r;

	struct evhttp_uri *http_uri = NULL;
	const char *url = NULL, *data_file = NULL;
	const char *crt = "/etc/ssl/certs/ca-certificates.crt";
	const char *scheme, *host, *path, *query;
	char uri[256];
	int port;
	int retries = 0;
	int timeout = -1;

	SSL_CTX *ssl_ctx = NULL;
	SSL *ssl = NULL;
	struct bufferevent *bev;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req;
	struct evkeyvalq *output_headers;
	struct evbuffer *output_buffer;

	int i;
	int ret = 0;
	enum { HTTP, HTTPS } type = HTTP;

	for (i = 1; i < argc; i++) {
		if (!strcmp("-url", argv[i])) {
			if (i < argc - 1) {
				url = argv[i + 1];
			} else {
				syntax();
				goto error;
			}
		} else if (!strcmp("-crt", argv[i])) {
			if (i < argc - 1) {
				crt = argv[i + 1];
			} else {
				syntax();
				goto error;
			}
		} else if (!strcmp("-ignore-cert", argv[i])) {
			ignore_cert = 1;
		} else if (!strcmp("-data", argv[i])) {
			if (i < argc - 1) {
				data_file = argv[i + 1];
			} else {
				syntax();
				goto error;
			}
		} else if (!strcmp("-retries", argv[i])) {
			if (i < argc - 1) {
				retries = atoi(argv[i + 1]);
			} else {
				syntax();
				goto error;
			}
		} else if (!strcmp("-timeout", argv[i])) {
			if (i < argc - 1) {
				timeout = atoi(argv[i + 1]);
			} else {
				syntax();
				goto error;
			}
		} else if (!strcmp("-help", argv[i])) {
			syntax();
			goto error;
		}
	}

	if (!url) {
		syntax();
		goto error;
	}

#ifdef _WIN32
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;

		wVersionRequested = MAKEWORD(2, 2);

		err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0) {
			printf("WSAStartup failed with error: %d\n", err);
			goto error;
		}
	}
#endif // _WIN32

	http_uri = evhttp_uri_parse(url);
	if (http_uri == NULL) {
		err("malformed url");
		goto error;
	}

	scheme = evhttp_uri_get_scheme(http_uri);
	if (scheme == NULL || (strcasecmp(scheme, "https") != 0 &&
	                       strcasecmp(scheme, "http") != 0)) {
		err("url must be http or https");
		goto error;
	}

	host = evhttp_uri_get_host(http_uri);
	if (host == NULL) {
		err("url must have a host");
		goto error;
	}

	port = evhttp_uri_get_port(http_uri);
	if (port == -1) {
		port = (strcasecmp(scheme, "http") == 0) ? 80 : 443;
	}

	path = evhttp_uri_get_path(http_uri);
	if (strlen(path) == 0) {
		path = "/";
	}

	query = evhttp_uri_get_query(http_uri);
	if (query == NULL) {
		snprintf(uri, sizeof(uri) - 1, "%s", path);
	} else {
		snprintf(uri, sizeof(uri) - 1, "%s?%s", path, query);
	}
	uri[sizeof(uri) - 1] = '\0';

#if OPENSSL_VERSION_NUMBER < 0x10100000L
	// Initialize OpenSSL
	SSL_library_init();
	ERR_load_crypto_strings();
	SSL_load_error_strings();
	OpenSSL_add_all_algorithms();
#endif

	/* This isn't strictly necessary... OpenSSL performs RAND_poll
	 * automatically on first use of random number generator. */
	r = RAND_poll();
	if (r == 0) {
		err_openssl("RAND_poll");
		goto error;
	}

	/* Create a new OpenSSL context */
	ssl_ctx = SSL_CTX_new(SSLv23_method());
	if (!ssl_ctx) {
		err_openssl("SSL_CTX_new");
		goto error;
	}

#ifndef _WIN32
	/* TODO: Add certificate loading on Windows as well */

	/* Attempt to use the system's trusted root certificates.
	 * (This path is only valid for Debian-based systems.) */
	if (1 != SSL_CTX_load_verify_locations(ssl_ctx, crt, NULL)) {
		err_openssl("SSL_CTX_load_verify_locations");
		goto error;
	}
	/* Ask OpenSSL to verify the server certificate.  Note that this
	 * does NOT include verifying that the hostname is correct.
	 * So, by itself, this means anyone with any legitimate
	 * CA-issued certificate for any website, can impersonate any
	 * other website in the world.  This is not good.  See "The
	 * Most Dangerous Code in the World" article at
	 * https://crypto.stanford.edu/~dabo/pubs/abstracts/ssl-client-bugs.html
	 */
	SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER, NULL);
	/* This is how we solve the problem mentioned in the previous
	 * comment.  We "wrap" OpenSSL's validation routine in our
	 * own routine, which also validates the hostname by calling
	 * the code provided by iSECPartners.  Note that even though
	 * the "Everything You've Always Wanted to Know About
	 * Certificate Validation With OpenSSL (But Were Afraid to
	 * Ask)" paper from iSECPartners says very explicitly not to
	 * call SSL_CTX_set_cert_verify_callback (at the bottom of
	 * page 2), what we're doing here is safe because our
	 * cert_verify_callback() calls X509_verify_cert(), which is
	 * OpenSSL's built-in routine which would have been called if
	 * we hadn't set the callback.  Therefore, we're just
	 * "wrapping" OpenSSL's routine, not replacing it. */
	SSL_CTX_set_cert_verify_callback(ssl_ctx, cert_verify_callback,
					  (void *) host);
#else // _WIN32
	(void)crt;
#endif // _WIN32

	// Create event base
	base = event_base_new();
	if (!base) {
		perror("event_base_new()");
		goto error;
	}

	// Create OpenSSL bufferevent and stack evhttp on top of it
	ssl = SSL_new(ssl_ctx);
	if (ssl == NULL) {
		err_openssl("SSL_new()");
		goto error;
	}

	#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
	// Set hostname for SNI extension
	SSL_set_tlsext_host_name(ssl, host);
	#endif

	if (strcasecmp(scheme, "http") == 0) {
		bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
	} else {
		type = HTTPS;
		bev = bufferevent_openssl_socket_new(base, -1, ssl,
			BUFFEREVENT_SSL_CONNECTING,
			BEV_OPT_CLOSE_ON_FREE|BEV_OPT_DEFER_CALLBACKS);
	}

	if (bev == NULL) {
		fprintf(stderr, "bufferevent_openssl_socket_new() failed\n");
		goto error;
	}

	bufferevent_openssl_set_allow_dirty_shutdown(bev, 1);

	// For simplicity, we let DNS resolution block. Everything else should be
	// asynchronous though.
	evcon = evhttp_connection_base_bufferevent_new(base, NULL, bev,
		host, port);
	if (evcon == NULL) {
		fprintf(stderr, "evhttp_connection_base_bufferevent_new() failed\n");
		goto error;
	}

	if (retries > 0) {
		evhttp_connection_set_retries(evcon, retries);
	}
	if (timeout >= 0) {
		evhttp_connection_set_timeout(evcon, timeout);
	}

	// Fire off the request
	req = evhttp_request_new(http_request_done, bev);
	if (req == NULL) {
		fprintf(stderr, "evhttp_request_new() failed\n");
		goto error;
	}

	output_headers = evhttp_request_get_output_headers(req);
	evhttp_add_header(output_headers, "Host", host);
	evhttp_add_header(output_headers, "Connection", "close");

	if (data_file) {
		/* NOTE: In production code, you'd probably want to use
		 * evbuffer_add_file() or evbuffer_add_file_segment(), to
		 * avoid needless copying. */
		FILE * f = fopen(data_file, "rb");
		char buf[1024];
		size_t s;
		size_t bytes = 0;

		if (!f) {
			syntax();
			goto error;
		}

		output_buffer = evhttp_request_get_output_buffer(req);
		while ((s = fread(buf, 1, sizeof(buf), f)) > 0) {
			evbuffer_add(output_buffer, buf, s);
			bytes += s;
		}
		evutil_snprintf(buf, sizeof(buf)-1, "%lu", (unsigned long)bytes);
		evhttp_add_header(output_headers, "Content-Length", buf);
		fclose(f);
	}

	r = evhttp_make_request(evcon, req, data_file ? EVHTTP_REQ_POST : EVHTTP_REQ_GET, uri);
	if (r != 0) {
		fprintf(stderr, "evhttp_make_request() failed\n");
		goto error;
	}

	event_base_dispatch(base);
	goto cleanup;

error:
	ret = 1;
cleanup:
	if (evcon)
		evhttp_connection_free(evcon);
	if (http_uri)
		evhttp_uri_free(http_uri);
	event_base_free(base);

	if (ssl_ctx)
		SSL_CTX_free(ssl_ctx);
	if (type == HTTP && ssl)
		SSL_free(ssl);
#if OPENSSL_VERSION_NUMBER < 0x10100000L
	EVP_cleanup();
	ERR_free_strings();

#ifdef EVENT__HAVE_ERR_REMOVE_THREAD_STATE
	ERR_remove_thread_state(NULL);
#else
	ERR_remove_state(0);
#endif
	CRYPTO_cleanup_all_ex_data();

	sk_SSL_COMP_free(SSL_COMP_get_compression_methods());
#endif /*OPENSSL_VERSION_NUMBER < 0x10100000L */

#ifdef _WIN32
	WSACleanup();
#endif

	return ret;
}