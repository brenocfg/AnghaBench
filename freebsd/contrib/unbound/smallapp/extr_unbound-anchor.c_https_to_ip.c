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
struct ip_list {int dummy; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TLS_initiate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TLS_shutdown (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int connect_to_ip (struct ip_list*) ; 
 int /*<<< orphan*/  fd_close (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * read_http_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * setup_sslctx () ; 
 scalar_t__ verb ; 
 int /*<<< orphan*/  write_http_get (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static BIO*
https_to_ip(struct ip_list* ip, const char* pathname, const char* urlname)
{
	int fd;
	SSL* ssl;
	BIO* bio;
	SSL_CTX* sslctx = setup_sslctx();
	if(!sslctx) {
		return NULL;
	}
	fd = connect_to_ip(ip);
	if(fd == -1) {
		SSL_CTX_free(sslctx);
		return NULL;
	}
	ssl = TLS_initiate(sslctx, fd);
	if(!ssl) {
		SSL_CTX_free(sslctx);
		fd_close(fd);
		return NULL;
	}
	if(!write_http_get(ssl, pathname, urlname)) {
		if(verb) printf("could not write to server\n");
		SSL_free(ssl);
		SSL_CTX_free(sslctx);
		fd_close(fd);
		return NULL;
	}
	bio = read_http_result(ssl);
	TLS_shutdown(fd, ssl, sslctx);
	return bio;
}