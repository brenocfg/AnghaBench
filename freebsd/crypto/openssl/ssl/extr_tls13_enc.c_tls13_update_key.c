#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secret ;
typedef  int /*<<< orphan*/  application_traffic ;
struct TYPE_10__ {int /*<<< orphan*/  enc_write_state; } ;
struct TYPE_11__ {int server; unsigned char* server_app_traffic_secret; unsigned char* client_app_traffic_secret; unsigned char* write_iv; unsigned char* read_iv; TYPE_3__ statem; TYPE_2__* s3; int /*<<< orphan*/  rlayer; int /*<<< orphan*/ * enc_read_ctx; int /*<<< orphan*/ * enc_write_ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  new_sym_enc; } ;
struct TYPE_9__ {TYPE_1__ tmp; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_WRITE_STATE_INVALID ; 
 int /*<<< orphan*/  ENC_WRITE_STATE_VALID ; 
 int EVP_MAX_MD_SIZE ; 
 size_t EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  RECORD_LAYER_reset_read_sequence (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORD_LAYER_reset_write_sequence (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  derive_secret_key_and_iv (TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,unsigned char const*,int,unsigned char*,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * ssl_handshake_md (TYPE_4__*) ; 

int tls13_update_key(SSL *s, int sending)
{
#ifdef CHARSET_EBCDIC
  static const unsigned char application_traffic[] = { 0x74, 0x72 ,0x61 ,0x66 ,0x66 ,0x69 ,0x63 ,0x20 ,0x75 ,0x70 ,0x64, 0x00};
#else
  static const unsigned char application_traffic[] = "traffic upd";
#endif
    const EVP_MD *md = ssl_handshake_md(s);
    size_t hashlen = EVP_MD_size(md);
    unsigned char *insecret, *iv;
    unsigned char secret[EVP_MAX_MD_SIZE];
    EVP_CIPHER_CTX *ciph_ctx;
    int ret = 0;

    if (s->server == sending)
        insecret = s->server_app_traffic_secret;
    else
        insecret = s->client_app_traffic_secret;

    if (sending) {
        s->statem.enc_write_state = ENC_WRITE_STATE_INVALID;
        iv = s->write_iv;
        ciph_ctx = s->enc_write_ctx;
        RECORD_LAYER_reset_write_sequence(&s->rlayer);
    } else {
        iv = s->read_iv;
        ciph_ctx = s->enc_read_ctx;
        RECORD_LAYER_reset_read_sequence(&s->rlayer);
    }

    if (!derive_secret_key_and_iv(s, sending, ssl_handshake_md(s),
                                  s->s3->tmp.new_sym_enc, insecret, NULL,
                                  application_traffic,
                                  sizeof(application_traffic) - 1, secret, iv,
                                  ciph_ctx)) {
        /* SSLfatal() already called */
        goto err;
    }

    memcpy(insecret, secret, hashlen);

    s->statem.enc_write_state = ENC_WRITE_STATE_VALID;
    ret = 1;
 err:
    OPENSSL_cleanse(secret, sizeof(secret));
    return ret;
}