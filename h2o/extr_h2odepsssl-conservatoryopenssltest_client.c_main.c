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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_ssl (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * BIO_new_ssl_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_conn_hostname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_ssl_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_free_strings () ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_cleanup () ; 
 scalar_t__ MatchFound ; 
 int RAND_status () ; 
 int /*<<< orphan*/  SECURE_CIPHER_LIST ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int SSL_CTX_load_verify_locations (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int SSL_CTX_set_cipher_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 scalar_t__ SSL_do_handshake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 long SSL_get_verify_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  TARGET_HOST ; 
 int /*<<< orphan*/  TARGET_SERVER ; 
 int /*<<< orphan*/  TLSv1_client_method () ; 
 int /*<<< orphan*/  TRUSTED_CA_PATHNAME ; 
 long X509_V_OK ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 char* X509_verify_cert_error_string (long) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  send_http_get_and_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ validate_hostname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[]) {
	BIO *sbio;
	SSL_CTX *ssl_ctx;
	SSL *ssl;
	X509 *server_cert;

	// Initialize OpenSSL
	SSL_library_init();
	SSL_load_error_strings();

 	// Check OpenSSL PRNG
	if(RAND_status() != 1) {
		fprintf(stderr, "OpenSSL PRNG not seeded with enough data.");
		goto error_1;
	}

	ssl_ctx = SSL_CTX_new(TLSv1_client_method());
	
	// Enable certificate validation
	SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER, NULL);
	// Configure the CA trust store to be used
	if (SSL_CTX_load_verify_locations(ssl_ctx, TRUSTED_CA_PATHNAME, NULL) != 1) {
		fprintf(stderr, "Couldn't load certificate trust store.\n");
		goto error_2;
	}

	// Only support secure cipher suites
	if (SSL_CTX_set_cipher_list(ssl_ctx, SECURE_CIPHER_LIST) != 1)
		goto error_2;

	// Create the SSL connection
	sbio = BIO_new_ssl_connect(ssl_ctx);
	BIO_get_ssl(sbio, &ssl); 
	if(!ssl) {
	  fprintf(stderr, "Can't locate SSL pointer\n");
		goto error_3;
	}

	// Do the SSL handshake
	BIO_set_conn_hostname(sbio, TARGET_SERVER);
	if(SSL_do_handshake(ssl) <= 0) {
		// SSL Handshake failed
		long verify_err = SSL_get_verify_result(ssl);
		if (verify_err != X509_V_OK) { 
			// It failed because the certificate chain validation failed
			fprintf(stderr, "Certificate chain validation failed: %s\n", X509_verify_cert_error_string(verify_err));
		}
		else {
			// It failed for another reason
			ERR_print_errors_fp(stderr);
		}
		goto error_3;
	}

	// Recover the server's certificate
	server_cert =  SSL_get_peer_certificate(ssl);
	if (server_cert == NULL) {
		// The handshake was successful although the server did not provide a certificate
		// Most likely using an insecure anonymous cipher suite... get out!
		goto error_4;
	}

	// Validate the hostname
	if (validate_hostname(TARGET_HOST, server_cert) != MatchFound) {
		fprintf(stderr, "Hostname validation failed.\n");
		goto error_5;
	}

	// Hostname validation succeeded; we can start sending data
	send_http_get_and_print(sbio);


error_5:
	X509_free(server_cert);

error_4:
	BIO_ssl_shutdown(sbio);

error_3:
	BIO_free_all(sbio);

error_2:
	SSL_CTX_free(ssl_ctx);

error_1: // OpenSSL cleanup
    EVP_cleanup();
    ERR_free_strings();

	return 0;
}