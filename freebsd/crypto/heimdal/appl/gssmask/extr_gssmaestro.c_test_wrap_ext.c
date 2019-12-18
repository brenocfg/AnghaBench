#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct client {int /*<<< orphan*/  moniker; } ;
struct TYPE_12__ {char* data; int length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ GSMERR_ERROR ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_1__*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ unwrap_token_ext (struct client*,scalar_t__,int,int,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 scalar_t__ wrap_token_ext (struct client*,scalar_t__,int,int,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int32_t
test_wrap_ext(struct client *c1, int32_t hc1, struct client *c2, int32_t hc2,
	      int conf, int bflags)
{
    krb5_data header, msg, trailer, wrapped, out;
    int32_t val;

    header.data = "header";
    header.length = 6;

    msg.data = "0123456789abcdef"; /* padded for most enctypes */
    msg.length = 32;

    trailer.data = "trailer";
    trailer.length = 7;

    krb5_data_zero(&wrapped);
    krb5_data_zero(&out);

    val = wrap_token_ext(c1, hc1, conf, bflags, &header, &msg, &trailer, &wrapped);
    if (val) {
	warnx("encrypt_token failed to host: %s", c1->moniker);
	return val;
    }
    val = unwrap_token_ext(c2, hc2, conf, bflags, &header, &wrapped, &trailer, &out);
    if (val) {
	krb5_data_free(&wrapped);
	warnx("decrypt_token failed to host: %s", c2->moniker);
	return val;
    }

    if (msg.length != out.length) {
	warnx("decrypted'ed token have wrong length (%lu != %lu)",
	      (unsigned long)msg.length, (unsigned long)out.length);
	val = GSMERR_ERROR;
    } else if (memcmp(msg.data, out.data, msg.length) != 0) {
	warnx("decryptd'ed token have wrong data");
	val = GSMERR_ERROR;
    }

    krb5_data_free(&wrapped);
    krb5_data_free(&out);
    return val;
}