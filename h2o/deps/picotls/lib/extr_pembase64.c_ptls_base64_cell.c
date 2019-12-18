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
 char* ptls_base64_alphabet ; 

__attribute__((used)) static void ptls_base64_cell(const uint8_t *data, char *text)
{
    int n[4];

    n[0] = data[0] >> 2;
    n[1] = ((data[0] & 3) << 4) | (data[1] >> 4);
    n[2] = ((data[1] & 15) << 2) | (data[2] >> 6);
    n[3] = data[2] & 63;

    for (int i = 0; i < 4; i++) {
        text[i] = ptls_base64_alphabet[n[i]];
    }
}