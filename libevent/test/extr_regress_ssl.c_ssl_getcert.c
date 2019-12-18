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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 scalar_t__ ASN1_INTEGER_set (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  MBSTRING_ASC ; 
 int NID_undef ; 
 int OBJ_txt2nid (char*) ; 
 scalar_t__ X509_NAME_add_entry_by_NID (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_new () ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_notAfter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_notBefore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_serialNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_new () ; 
 int /*<<< orphan*/  X509_set_issuer_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_set_pubkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_set_subject_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ X509_set_version (int /*<<< orphan*/ *,int) ; 
 scalar_t__ X509_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_time_adj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

X509 *
ssl_getcert(EVP_PKEY *key)
{
	/* Dummy code to make a quick-and-dirty valid certificate with
	   OpenSSL.  Don't copy this code into your own program! It does a
	   number of things in a stupid and insecure way. */
	X509 *x509 = NULL;
	X509_NAME *name = NULL;
	int nid;
	time_t now = time(NULL);

	tt_assert(key);

	x509 = X509_new();
	tt_assert(x509);
	tt_assert(0 != X509_set_version(x509, 2));
	tt_assert(0 != ASN1_INTEGER_set(X509_get_serialNumber(x509),
		(long)now));

	name = X509_NAME_new();
	tt_assert(name);
	nid = OBJ_txt2nid("commonName");
	tt_assert(NID_undef != nid);
	tt_assert(0 != X509_NAME_add_entry_by_NID(
		    name, nid, MBSTRING_ASC, (unsigned char*)"example.com",
		    -1, -1, 0));

	X509_set_subject_name(x509, name);
	X509_set_issuer_name(x509, name);
	X509_NAME_free(name);

	X509_time_adj(X509_get_notBefore(x509), 0, &now);
	now += 3600;
	X509_time_adj(X509_get_notAfter(x509), 0, &now);
	X509_set_pubkey(x509, key);
	tt_assert(0 != X509_sign(x509, key, EVP_sha1()));

	return x509;
end:
	X509_free(x509);
	X509_NAME_free(name);
	return NULL;
}