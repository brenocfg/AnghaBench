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
struct ssl_context {int /*<<< orphan*/  pkey; int /*<<< orphan*/  cert; } ;
typedef  int /*<<< orphan*/  X509_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  MBSTRING_ASC ; 
 int /*<<< orphan*/  X509_NAME_add_entry_by_txt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_notAfter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_notBefore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_serialNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_get_subject_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_gmtime_adj (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  X509_new () ; 
 int /*<<< orphan*/  X509_set_issuer_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_set_pubkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_sign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ssl_load_cert(struct ssl_context *ssl)
{
	X509_NAME *name;

	ssl->cert = X509_new();

	ASN1_INTEGER_set(X509_get_serialNumber(ssl->cert), 1);

	X509_gmtime_adj(X509_get_notBefore(ssl->cert), 0);
	/** 1 year lifetime */
	X509_gmtime_adj(X509_get_notAfter(ssl->cert),
		(long)time(NULL) + 365 * 86400);

	X509_set_pubkey(ssl->cert, ssl->pkey);

	name = X509_get_subject_name(ssl->cert);
	X509_NAME_add_entry_by_txt(
		name, "C", MBSTRING_ASC, (unsigned char *)"--", -1, -1, 0);
	X509_NAME_add_entry_by_txt(
		name, "O", MBSTRING_ASC, (unsigned char *)"<NULL>", -1, -1, 0);
	X509_NAME_add_entry_by_txt(
		name, "CN", MBSTRING_ASC, (unsigned char *)"*", -1, -1, 0);
	X509_set_issuer_name(ssl->cert, name);

	X509_sign(ssl->cert, ssl->pkey, EVP_sha1());

	return 0;
}