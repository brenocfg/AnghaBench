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
typedef  int /*<<< orphan*/  WSADATA ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int STACK_OF (int /*<<< orphan*/ ) ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509 ; 
 int /*<<< orphan*/  X509_free ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ *) ; 
 int cert ; 
 int /*<<< orphan*/  do_wsa_cleanup ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * https (struct ip_list*,char const*,char const*) ; 
 int /*<<< orphan*/  ip_list_free (struct ip_list*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_cert_or_builtin (char const*) ; 
 struct ip_list* resolve_name (char const*,int,char const*,char const*,char const*,int,int) ; 
 int /*<<< orphan*/  sk_X509_pop_free (int,int /*<<< orphan*/ ) ; 
 scalar_t__ verb ; 
 int /*<<< orphan*/  verify_and_update_anchor (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char const*) ; 
 char* wsa_strerror (int) ; 

__attribute__((used)) static int
do_certupdate(const char* root_anchor_file, const char* root_cert_file,
	const char* urlname, const char* xmlname, const char* p7sname,
	const char* p7signer, const char* res_conf, const char* root_hints,
	const char* debugconf, int ip4only, int ip6only, int port)
{
	STACK_OF(X509)* cert;
	BIO *xml, *p7s;
	struct ip_list* ip_list = NULL;

	/* read pem file or provide builtin */
	cert = read_cert_or_builtin(root_cert_file);

	/* lookup A, AAAA for the urlname (or parse urlname if IP address) */
	ip_list = resolve_name(urlname, port, res_conf, root_hints, debugconf,
		ip4only, ip6only);

#ifdef USE_WINSOCK
	if(1) { /* libunbound finished, startup WSA for the https connection */
		WSADATA wsa_data;
		int r;
		if((r = WSAStartup(MAKEWORD(2,2), &wsa_data)) != 0) {
			if(verb) printf("WSAStartup failed: %s\n",
				wsa_strerror(r));
			exit(0);
		}
		atexit(&do_wsa_cleanup);
	}
#endif

	/* fetch the necessary files over HTTPS */
	xml = https(ip_list, xmlname, urlname);
	p7s = https(ip_list, p7sname, urlname);

	/* verify and update the root anchor */
	verify_and_update_anchor(root_anchor_file, xml, p7s, cert, p7signer);
	if(verb) printf("success: the anchor has been updated "
			"using the cert\n");

	BIO_free(xml);
	BIO_free(p7s);
#ifndef S_SPLINT_S
	sk_X509_pop_free(cert, X509_free);
#endif
	ip_list_free(ip_list);
	return 1;
}