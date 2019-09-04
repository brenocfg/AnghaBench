#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/  cb; } ;
struct st_util_save_ticket_t {TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  ptls_t ;
typedef  int /*<<< orphan*/  ptls_key_exchange_algorithm_t ;
struct TYPE_12__ {int /*<<< orphan*/ * member_0; } ;
struct TYPE_11__ {TYPE_4__ member_0; } ;
struct TYPE_10__ {TYPE_3__ member_0; } ;
struct TYPE_13__ {TYPE_2__ member_0; } ;
typedef  TYPE_5__ ptls_handshake_properties_t ;
struct TYPE_14__ {TYPE_1__* save_ticket; int /*<<< orphan*/ * verify_certificate; int /*<<< orphan*/ ** member_3; int /*<<< orphan*/ ** member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ ptls_context_t ;
typedef  int /*<<< orphan*/  ptls_cipher_suite_t ;
typedef  int /*<<< orphan*/  ptls_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  deterministic_random_bytes ; 
 int /*<<< orphan*/  fake_ticket_cb ; 
 int /*<<< orphan*/  ptls_buffer_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_buffer_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_get_time ; 
 int ptls_handshake (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,TYPE_5__*) ; 
 int /*<<< orphan*/ * ptls_new (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_openssl_aes128gcmsha256 ; 
 int /*<<< orphan*/  ptls_openssl_secp256r1 ; 
 int /*<<< orphan*/  ptls_receive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // key exchanges
  ptls_key_exchange_algorithm_t *key_exchanges[128] = {NULL};
  key_exchanges[0] = &ptls_openssl_secp256r1;
  ptls_cipher_suite_t *cipher_suites[] = {&ptls_openssl_aes128gcmsha256, NULL};

  // create ptls_context_t
  ptls_context_t ctx_client = {deterministic_random_bytes, &ptls_get_time,
                               key_exchanges, cipher_suites};
  ctx_client.verify_certificate = NULL;

  // create pls_t
  ptls_t *tls_client = ptls_new(&ctx_client, 0);  // 0: client

  // fake ticket saving
  static struct st_util_save_ticket_t st;
  st.super.cb = fake_ticket_cb;
  ctx_client.save_ticket = &st.super;

  // empty hsprop
  ptls_handshake_properties_t hsprop = {{{{NULL}}}};

  // buffers
  ptls_buffer_t client_encbuf;
  ptls_buffer_init(&client_encbuf, "", 0);

  // generate client_hello
  ptls_handshake(tls_client, &client_encbuf, NULL, 0, &hsprop);

  // reset buffer
  ptls_buffer_dispose(&client_encbuf);
  ptls_buffer_init(&client_encbuf, "", 0);

  // accept server
  size_t consumed = size;
  int ret =
      ptls_handshake(tls_client, &client_encbuf, data, &consumed, &hsprop);

  // more messages to parse?
  if (ret == 0 && size - consumed > 0) {
    size = size - consumed;
    // reset buffer
    ptls_buffer_dispose(&client_encbuf);
    ptls_buffer_init(&client_encbuf, "", 0);
    // receive messages
    ptls_receive(tls_client, &client_encbuf, data + consumed, &size);
  }

  // cleaning
  ptls_buffer_dispose(&client_encbuf);
  ptls_free(tls_client);

  return 0;
}