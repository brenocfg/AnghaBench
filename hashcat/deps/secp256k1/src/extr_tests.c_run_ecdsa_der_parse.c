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

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int count ; 
 int /*<<< orphan*/  damage_array (unsigned char*,size_t*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  random_ber_signature (unsigned char*,size_t*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int test_ecdsa_der_parse (unsigned char*,size_t,int,int) ; 

void run_ecdsa_der_parse(void) {
    int i,j;
    for (i = 0; i < 200 * count; i++) {
        unsigned char buffer[2048];
        size_t buflen = 0;
        int certainly_der = 0;
        int certainly_not_der = 0;
        random_ber_signature(buffer, &buflen, &certainly_der, &certainly_not_der);
        CHECK(buflen <= 2048);
        for (j = 0; j < 16; j++) {
            int ret = 0;
            if (j > 0) {
                damage_array(buffer, &buflen);
                /* We don't know anything anymore about the DERness of the result */
                certainly_der = 0;
                certainly_not_der = 0;
            }
            ret = test_ecdsa_der_parse(buffer, buflen, certainly_der, certainly_not_der);
            if (ret != 0) {
                size_t k;
                fprintf(stderr, "Failure %x on ", ret);
                for (k = 0; k < buflen; k++) {
                    fprintf(stderr, "%02x ", buffer[k]);
                }
                fprintf(stderr, "\n");
            }
            CHECK(ret == 0);
        }
    }
}