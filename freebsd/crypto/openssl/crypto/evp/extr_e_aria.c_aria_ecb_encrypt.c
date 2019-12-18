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
typedef  int /*<<< orphan*/  ARIA_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  aria_encrypt (unsigned char const*,unsigned char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void aria_ecb_encrypt(const unsigned char *in, unsigned char *out,
                             const ARIA_KEY *key, const int enc)
{
    aria_encrypt(in, out, key);
}