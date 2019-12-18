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
typedef  int /*<<< orphan*/  uint8_t ;
struct uECC_Curve_t {int dummy; } ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  uECC_make_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct uECC_Curve_t const*) ; 
 struct uECC_Curve_t* uECC_secp160r1 () ; 
 struct uECC_Curve_t* uECC_secp192r1 () ; 
 struct uECC_Curve_t* uECC_secp224r1 () ; 
 struct uECC_Curve_t* uECC_secp256k1 () ; 
 struct uECC_Curve_t* uECC_secp256r1 () ; 
 int /*<<< orphan*/  uECC_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct uECC_Curve_t const*) ; 
 int /*<<< orphan*/  uECC_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct uECC_Curve_t const*) ; 

int main() {
    int i, c;
    uint8_t private[32] = {0};
    uint8_t public[64] = {0};
    uint8_t hash[32] = {0};
    uint8_t sig[64] = {0};

    const struct uECC_Curve_t * curves[5];
    int num_curves = 0;
#if uECC_SUPPORTS_secp160r1
    curves[num_curves++] = uECC_secp160r1();
#endif
#if uECC_SUPPORTS_secp192r1
    curves[num_curves++] = uECC_secp192r1();
#endif
#if uECC_SUPPORTS_secp224r1
    curves[num_curves++] = uECC_secp224r1();
#endif
#if uECC_SUPPORTS_secp256r1
    curves[num_curves++] = uECC_secp256r1();
#endif
#if uECC_SUPPORTS_secp256k1
    curves[num_curves++] = uECC_secp256k1();
#endif
    
    printf("Testing 256 signatures\n");
    for (c = 0; c < num_curves; ++c) {
        for (i = 0; i < 256; ++i) {
            printf(".");
            fflush(stdout);

            if (!uECC_make_key(public, private, curves[c])) {
                printf("uECC_make_key() failed\n");
                return 1;
            }
            memcpy(hash, public, sizeof(hash));
            
            if (!uECC_sign(private, hash, sizeof(hash), sig, curves[c])) {
                printf("uECC_sign() failed\n");
                return 1;
            }

            if (!uECC_verify(public, hash, sizeof(hash), sig, curves[c])) {
                printf("uECC_verify() failed\n");
                return 1;
            }
        }
        printf("\n");
    }
    
    return 0;
}