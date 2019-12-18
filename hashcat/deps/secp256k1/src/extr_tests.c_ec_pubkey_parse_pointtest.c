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
typedef  unsigned char secp256k1_pubkey ;
typedef  int /*<<< orphan*/  secp256k1_ge ;
typedef  int /*<<< orphan*/  pubkey ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  SECP256K1_EC_COMPRESSED ; 
 int /*<<< orphan*/  SECP256K1_EC_UNCOMPRESSED ; 
 int /*<<< orphan*/  VG_CHECK (unsigned char*,int) ; 
 int /*<<< orphan*/  VG_UNDEF (unsigned char*,int) ; 
 int /*<<< orphan*/ * counting_illegal_callback_fn ; 
 int /*<<< orphan*/  ctx ; 
 scalar_t__ memcmp (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  secp256k1_context_set_illegal_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int secp256k1_ec_pubkey_parse (int /*<<< orphan*/ ,unsigned char*,unsigned char*,size_t) ; 
 int secp256k1_ec_pubkey_serialize (int /*<<< orphan*/ ,unsigned char*,size_t*,unsigned char*,int /*<<< orphan*/ ) ; 
 int secp256k1_pubkey_load (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  secp256k1_pubkey_save (unsigned char*,int /*<<< orphan*/ *) ; 

void ec_pubkey_parse_pointtest(const unsigned char *input, int xvalid, int yvalid) {
    unsigned char pubkeyc[65];
    secp256k1_pubkey pubkey;
    secp256k1_ge ge;
    size_t pubkeyclen;
    int32_t ecount;
    ecount = 0;
    secp256k1_context_set_illegal_callback(ctx, counting_illegal_callback_fn, &ecount);
    for (pubkeyclen = 3; pubkeyclen <= 65; pubkeyclen++) {
        /* Smaller sizes are tested exhaustively elsewhere. */
        int32_t i;
        memcpy(&pubkeyc[1], input, 64);
        VG_UNDEF(&pubkeyc[pubkeyclen], 65 - pubkeyclen);
        for (i = 0; i < 256; i++) {
            /* Try all type bytes. */
            int xpass;
            int ypass;
            int ysign;
            pubkeyc[0] = i;
            /* What sign does this point have? */
            ysign = (input[63] & 1) + 2;
            /* For the current type (i) do we expect parsing to work? Handled all of compressed/uncompressed/hybrid. */
            xpass = xvalid && (pubkeyclen == 33) && ((i & 254) == 2);
            /* Do we expect a parse and re-serialize as uncompressed to give a matching y? */
            ypass = xvalid && yvalid && ((i & 4) == ((pubkeyclen == 65) << 2)) &&
                ((i == 4) || ((i & 251) == ysign)) && ((pubkeyclen == 33) || (pubkeyclen == 65));
            if (xpass || ypass) {
                /* These cases must parse. */
                unsigned char pubkeyo[65];
                size_t outl;
                memset(&pubkey, 0, sizeof(pubkey));
                VG_UNDEF(&pubkey, sizeof(pubkey));
                ecount = 0;
                CHECK(secp256k1_ec_pubkey_parse(ctx, &pubkey, pubkeyc, pubkeyclen) == 1);
                VG_CHECK(&pubkey, sizeof(pubkey));
                outl = 65;
                VG_UNDEF(pubkeyo, 65);
                CHECK(secp256k1_ec_pubkey_serialize(ctx, pubkeyo, &outl, &pubkey, SECP256K1_EC_COMPRESSED) == 1);
                VG_CHECK(pubkeyo, outl);
                CHECK(outl == 33);
                CHECK(memcmp(&pubkeyo[1], &pubkeyc[1], 32) == 0);
                CHECK((pubkeyclen != 33) || (pubkeyo[0] == pubkeyc[0]));
                if (ypass) {
                    /* This test isn't always done because we decode with alternative signs, so the y won't match. */
                    CHECK(pubkeyo[0] == ysign);
                    CHECK(secp256k1_pubkey_load(ctx, &ge, &pubkey) == 1);
                    memset(&pubkey, 0, sizeof(pubkey));
                    VG_UNDEF(&pubkey, sizeof(pubkey));
                    secp256k1_pubkey_save(&pubkey, &ge);
                    VG_CHECK(&pubkey, sizeof(pubkey));
                    outl = 65;
                    VG_UNDEF(pubkeyo, 65);
                    CHECK(secp256k1_ec_pubkey_serialize(ctx, pubkeyo, &outl, &pubkey, SECP256K1_EC_UNCOMPRESSED) == 1);
                    VG_CHECK(pubkeyo, outl);
                    CHECK(outl == 65);
                    CHECK(pubkeyo[0] == 4);
                    CHECK(memcmp(&pubkeyo[1], input, 64) == 0);
                }
                CHECK(ecount == 0);
            } else {
                /* These cases must fail to parse. */
                memset(&pubkey, 0xfe, sizeof(pubkey));
                ecount = 0;
                VG_UNDEF(&pubkey, sizeof(pubkey));
                CHECK(secp256k1_ec_pubkey_parse(ctx, &pubkey, pubkeyc, pubkeyclen) == 0);
                VG_CHECK(&pubkey, sizeof(pubkey));
                CHECK(ecount == 0);
                CHECK(secp256k1_pubkey_load(ctx, &ge, &pubkey) == 0);
                CHECK(ecount == 1);
            }
        }
    }
    secp256k1_context_set_illegal_callback(ctx, NULL, NULL);
}