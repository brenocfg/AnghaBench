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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  TYPE_1__ SRTP_PROTECTION_PROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 
 int BUFSIZ ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  PEM_write_bio_SSL_SESSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PEM_write_bio_X509 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* SSL_CIPHER_get_name (int /*<<< orphan*/ ) ; 
 int SSL_OP_NO_RENEGOTIATION ; 
 int /*<<< orphan*/  SSL_export_keying_material (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get0_next_proto_negotiated (int /*<<< orphan*/ *,unsigned char const**,unsigned int*) ; 
 int /*<<< orphan*/  SSL_get_current_cipher (int /*<<< orphan*/ *) ; 
 int SSL_get_options (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_get_secure_renegotiation_support (int /*<<< orphan*/ *) ; 
 TYPE_1__* SSL_get_selected_srtp_profile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_shared_ciphers (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ SSL_session_reused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 unsigned char* app_malloc (int,char*) ; 
 int /*<<< orphan*/  bio_s_out ; 
 int /*<<< orphan*/  dump_cert_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * keymatexportlabel ; 
 int keymatexportlen ; 
 int /*<<< orphan*/  print_ca_names (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_ssl_summary (int /*<<< orphan*/ *) ; 
 scalar_t__ s_brief ; 
 int /*<<< orphan*/  ssl_print_groups (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_print_point_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_print_sigalgs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_connection_info(SSL *con)
{
    const char *str;
    X509 *peer;
    char buf[BUFSIZ];
#if !defined(OPENSSL_NO_NEXTPROTONEG)
    const unsigned char *next_proto_neg;
    unsigned next_proto_neg_len;
#endif
    unsigned char *exportedkeymat;
    int i;

    if (s_brief)
        print_ssl_summary(con);

    PEM_write_bio_SSL_SESSION(bio_s_out, SSL_get_session(con));

    peer = SSL_get_peer_certificate(con);
    if (peer != NULL) {
        BIO_printf(bio_s_out, "Client certificate\n");
        PEM_write_bio_X509(bio_s_out, peer);
        dump_cert_text(bio_s_out, peer);
        X509_free(peer);
        peer = NULL;
    }

    if (SSL_get_shared_ciphers(con, buf, sizeof(buf)) != NULL)
        BIO_printf(bio_s_out, "Shared ciphers:%s\n", buf);
    str = SSL_CIPHER_get_name(SSL_get_current_cipher(con));
    ssl_print_sigalgs(bio_s_out, con);
#ifndef OPENSSL_NO_EC
    ssl_print_point_formats(bio_s_out, con);
    ssl_print_groups(bio_s_out, con, 0);
#endif
    print_ca_names(bio_s_out, con);
    BIO_printf(bio_s_out, "CIPHER is %s\n", (str != NULL) ? str : "(NONE)");

#if !defined(OPENSSL_NO_NEXTPROTONEG)
    SSL_get0_next_proto_negotiated(con, &next_proto_neg, &next_proto_neg_len);
    if (next_proto_neg) {
        BIO_printf(bio_s_out, "NEXTPROTO is ");
        BIO_write(bio_s_out, next_proto_neg, next_proto_neg_len);
        BIO_printf(bio_s_out, "\n");
    }
#endif
#ifndef OPENSSL_NO_SRTP
    {
        SRTP_PROTECTION_PROFILE *srtp_profile
            = SSL_get_selected_srtp_profile(con);

        if (srtp_profile)
            BIO_printf(bio_s_out, "SRTP Extension negotiated, profile=%s\n",
                       srtp_profile->name);
    }
#endif
    if (SSL_session_reused(con))
        BIO_printf(bio_s_out, "Reused session-id\n");
    BIO_printf(bio_s_out, "Secure Renegotiation IS%s supported\n",
               SSL_get_secure_renegotiation_support(con) ? "" : " NOT");
    if ((SSL_get_options(con) & SSL_OP_NO_RENEGOTIATION))
        BIO_printf(bio_s_out, "Renegotiation is DISABLED\n");

    if (keymatexportlabel != NULL) {
        BIO_printf(bio_s_out, "Keying material exporter:\n");
        BIO_printf(bio_s_out, "    Label: '%s'\n", keymatexportlabel);
        BIO_printf(bio_s_out, "    Length: %i bytes\n", keymatexportlen);
        exportedkeymat = app_malloc(keymatexportlen, "export key");
        if (!SSL_export_keying_material(con, exportedkeymat,
                                        keymatexportlen,
                                        keymatexportlabel,
                                        strlen(keymatexportlabel),
                                        NULL, 0, 0)) {
            BIO_printf(bio_s_out, "    Error\n");
        } else {
            BIO_printf(bio_s_out, "    Keying material: ");
            for (i = 0; i < keymatexportlen; i++)
                BIO_printf(bio_s_out, "%02X", exportedkeymat[i]);
            BIO_printf(bio_s_out, "\n");
        }
        OPENSSL_free(exportedkeymat);
    }

    (void)BIO_flush(bio_s_out);
}