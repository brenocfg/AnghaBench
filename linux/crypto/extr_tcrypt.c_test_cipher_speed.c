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
typedef  int /*<<< orphan*/  u8 ;
struct cipher_speed_template {int dummy; } ;

/* Variables and functions */
 void test_skcipher_speed (char const*,int,unsigned int,struct cipher_speed_template*,unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_cipher_speed(const char *algo, int enc, unsigned int secs,
			      struct cipher_speed_template *template,
			      unsigned int tcount, u8 *keysize)
{
	return test_skcipher_speed(algo, enc, secs, template, tcount, keysize,
				   false);
}