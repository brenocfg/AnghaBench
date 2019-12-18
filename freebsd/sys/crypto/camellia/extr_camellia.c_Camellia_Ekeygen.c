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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  camellia_setup128 (unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  camellia_setup192 (unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  camellia_setup256 (unsigned char const*,int /*<<< orphan*/ *) ; 

void
Camellia_Ekeygen(const int keyBitLength, 
		 const unsigned char *rawKey, 
		 uint32_t *subkey)
{
    KASSERT(keyBitLength == 128 || keyBitLength == 192 || keyBitLength == 256,
	    ("Invalid key size (%d).", keyBitLength));

    switch(keyBitLength) {
    case 128:
	camellia_setup128(rawKey, subkey);
	break;
    case 192:
	camellia_setup192(rawKey, subkey);
	break;
    case 256:
	camellia_setup256(rawKey, subkey);
	break;
    default:
	break;
    }
}