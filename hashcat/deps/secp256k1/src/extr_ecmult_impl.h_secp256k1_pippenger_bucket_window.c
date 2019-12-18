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
 int PIPPENGER_MAX_BUCKET_WINDOW ; 

__attribute__((used)) static int secp256k1_pippenger_bucket_window(size_t n) {
#ifdef USE_ENDOMORPHISM
    if (n <= 1) {
        return 1;
    } else if (n <= 4) {
        return 2;
    } else if (n <= 20) {
        return 3;
    } else if (n <= 57) {
        return 4;
    } else if (n <= 136) {
        return 5;
    } else if (n <= 235) {
        return 6;
    } else if (n <= 1260) {
        return 7;
    } else if (n <= 4420) {
        return 9;
    } else if (n <= 7880) {
        return 10;
    } else if (n <= 16050) {
        return 11;
    } else {
        return PIPPENGER_MAX_BUCKET_WINDOW;
    }
#else
    if (n <= 1) {
        return 1;
    } else if (n <= 11) {
        return 2;
    } else if (n <= 45) {
        return 3;
    } else if (n <= 100) {
        return 4;
    } else if (n <= 275) {
        return 5;
    } else if (n <= 625) {
        return 6;
    } else if (n <= 1850) {
        return 7;
    } else if (n <= 3400) {
        return 8;
    } else if (n <= 9630) {
        return 9;
    } else if (n <= 17900) {
        return 10;
    } else if (n <= 32800) {
        return 11;
    } else {
        return PIPPENGER_MAX_BUCKET_WINDOW;
    }
#endif
}