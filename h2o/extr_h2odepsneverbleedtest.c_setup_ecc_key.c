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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int) ; 
 int NID_X9_62_prime256v1 ; 
 char* OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  SSL_CTX_set_tmp_ecdh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void setup_ecc_key(SSL_CTX *ssl_ctx)
{
    int nid = NID_X9_62_prime256v1;
    EC_KEY *key = EC_KEY_new_by_curve_name(nid);
    if (key == NULL) {
        fprintf(stderr, "Failed to create curve \"%s\"\n", OBJ_nid2sn(nid));
        return;
    }
    SSL_CTX_set_tmp_ecdh(ssl_ctx, key);
    EC_KEY_free(key);
}