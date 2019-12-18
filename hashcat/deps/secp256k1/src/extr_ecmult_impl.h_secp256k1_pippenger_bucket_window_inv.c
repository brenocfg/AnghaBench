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
#define  PIPPENGER_MAX_BUCKET_WINDOW 128 
 size_t SIZE_MAX ; 

__attribute__((used)) static size_t secp256k1_pippenger_bucket_window_inv(int bucket_window) {
    switch(bucket_window) {
#ifdef USE_ENDOMORPHISM
        case 1: return 1;
        case 2: return 4;
        case 3: return 20;
        case 4: return 57;
        case 5: return 136;
        case 6: return 235;
        case 7: return 1260;
        case 8: return 1260;
        case 9: return 4420;
        case 10: return 7880;
        case 11: return 16050;
        case PIPPENGER_MAX_BUCKET_WINDOW: return SIZE_MAX;
#else
        case 1: return 1;
        case 2: return 11;
        case 3: return 45;
        case 4: return 100;
        case 5: return 275;
        case 6: return 625;
        case 7: return 1850;
        case 8: return 3400;
        case 9: return 9630;
        case 10: return 17900;
        case 11: return 32800;
        case PIPPENGER_MAX_BUCKET_WINDOW: return SIZE_MAX;
#endif
    }
    return 0;
}