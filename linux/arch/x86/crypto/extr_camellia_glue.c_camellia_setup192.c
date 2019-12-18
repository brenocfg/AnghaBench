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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  camellia_setup256 (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static void camellia_setup192(const unsigned char *key, u64 *subkey)
{
	unsigned char kk[32];
	u64 krl, krr;

	memcpy(kk, key, 24);
	memcpy((unsigned char *)&krl, key+16, 8);
	krr = ~krl;
	memcpy(kk+24, (unsigned char *)&krr, 8);
	camellia_setup256(kk, subkey);
}