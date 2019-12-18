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
typedef  int /*<<< orphan*/  cf_poly1305 ;

/* Variables and functions */
 int /*<<< orphan*/  cf_poly1305_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zeros64 ; 

__attribute__((used)) static void chacha20poly1305_encrypt_pad(cf_poly1305 *poly, size_t n)
{
    if (n % 16 != 0)
        cf_poly1305_update(poly, zeros64, 16 - (n % 16));
}