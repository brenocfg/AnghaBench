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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  snprintf (char*,size_t const,char*,int const,int const) ; 

void
dnsc_key_to_fingerprint(char fingerprint[80U], const uint8_t * const key)
{
    const size_t fingerprint_size = 80U;
    size_t       fingerprint_pos = (size_t) 0U;
    size_t       key_pos = (size_t) 0U;

    for (;;) {
        assert(fingerprint_size > fingerprint_pos);
        snprintf(&fingerprint[fingerprint_pos],
                        fingerprint_size - fingerprint_pos, "%02X%02X",
                        key[key_pos], key[key_pos + 1U]);
        key_pos += 2U;
        if (key_pos >= crypto_box_PUBLICKEYBYTES) {
            break;
        }
        fingerprint[fingerprint_pos + 4U] = ':';
        fingerprint_pos += 5U;
    }
}