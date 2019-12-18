#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  num ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  TYPE_4__* gss_channel_bindings_t ;
struct TYPE_8__ {int length; int /*<<< orphan*/ * value; } ;
struct TYPE_7__ {int length; int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {int length; int /*<<< orphan*/ * value; } ;
struct TYPE_9__ {int initiator_addrtype; int acceptor_addrtype; TYPE_3__ application_data; TYPE_2__ acceptor_address; TYPE_1__ initiator_address; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  _gsskrb5_encode_om_uint32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
hash_input_chan_bindings (const gss_channel_bindings_t b,
			  u_char *p)
{
  u_char num[4];
  EVP_MD_CTX *ctx;

  ctx = EVP_MD_CTX_create();
  EVP_DigestInit_ex(ctx, EVP_md5(), NULL);

  _gsskrb5_encode_om_uint32 (b->initiator_addrtype, num);
  EVP_DigestUpdate(ctx, num, sizeof(num));
  _gsskrb5_encode_om_uint32 (b->initiator_address.length, num);
  EVP_DigestUpdate(ctx, num, sizeof(num));
  if (b->initiator_address.length)
      EVP_DigestUpdate(ctx,
		       b->initiator_address.value,
		       b->initiator_address.length);
  _gsskrb5_encode_om_uint32 (b->acceptor_addrtype, num);
  EVP_DigestUpdate(ctx, num, sizeof(num));
  _gsskrb5_encode_om_uint32 (b->acceptor_address.length, num);
  EVP_DigestUpdate(ctx, num, sizeof(num));
  if (b->acceptor_address.length)
      EVP_DigestUpdate(ctx,
		       b->acceptor_address.value,
		       b->acceptor_address.length);
  _gsskrb5_encode_om_uint32 (b->application_data.length, num);
  EVP_DigestUpdate(ctx, num, sizeof(num));
  if (b->application_data.length)
      EVP_DigestUpdate(ctx,
		       b->application_data.value,
		       b->application_data.length);
  EVP_DigestFinal_ex(ctx, p, NULL);
  EVP_MD_CTX_destroy(ctx);

  return 0;
}