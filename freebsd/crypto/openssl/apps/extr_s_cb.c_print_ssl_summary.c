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
typedef  int /*<<< orphan*/  SSL_CIPHER ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  SSL_CIPHER_get_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * SSL_get_current_cipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_get_peer_signature_nid (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ SSL_get_peer_signature_type_nid (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  SSL_get_version (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_is_server (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_print_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  do_print_sigalgs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_nameopt () ; 
 int /*<<< orphan*/  get_sigtype (int) ; 
 int /*<<< orphan*/  print_raw_cipherlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_verify_detail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_print_groups (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ssl_print_point_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_print_tmp_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void print_ssl_summary(SSL *s)
{
    const SSL_CIPHER *c;
    X509 *peer;

    BIO_printf(bio_err, "Protocol version: %s\n", SSL_get_version(s));
    print_raw_cipherlist(s);
    c = SSL_get_current_cipher(s);
    BIO_printf(bio_err, "Ciphersuite: %s\n", SSL_CIPHER_get_name(c));
    do_print_sigalgs(bio_err, s, 0);
    peer = SSL_get_peer_certificate(s);
    if (peer != NULL) {
        int nid;

        BIO_puts(bio_err, "Peer certificate: ");
        X509_NAME_print_ex(bio_err, X509_get_subject_name(peer),
                           0, get_nameopt());
        BIO_puts(bio_err, "\n");
        if (SSL_get_peer_signature_nid(s, &nid))
            BIO_printf(bio_err, "Hash used: %s\n", OBJ_nid2sn(nid));
        if (SSL_get_peer_signature_type_nid(s, &nid))
            BIO_printf(bio_err, "Signature type: %s\n", get_sigtype(nid));
        print_verify_detail(s, bio_err);
    } else {
        BIO_puts(bio_err, "No peer certificate\n");
    }
    X509_free(peer);
#ifndef OPENSSL_NO_EC
    ssl_print_point_formats(bio_err, s);
    if (SSL_is_server(s))
        ssl_print_groups(bio_err, s, 1);
    else
        ssl_print_tmp_key(bio_err, s);
#else
    if (!SSL_is_server(s))
        ssl_print_tmp_key(bio_err, s);
#endif
}