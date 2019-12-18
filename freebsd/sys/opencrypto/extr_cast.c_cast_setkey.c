#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
typedef  int u_int32_t ;
struct TYPE_3__ {int rounds; int* xkey; } ;
typedef  TYPE_1__ cast_key ;

/* Variables and functions */
 size_t U_INT8_Ta (int) ; 
 size_t U_INT8_Tb (int) ; 
 size_t U_INT8_Tc (int) ; 
 size_t U_INT8_Td (int) ; 
 int* cast_sbox5 ; 
 int* cast_sbox6 ; 
 int* cast_sbox7 ; 
 int* cast_sbox8 ; 

void cast_setkey(cast_key* key, const u_int8_t* rawkey, int keybytes)
{
u_int32_t t[4] = {0, 0, 0, 0}, z[4] = {0, 0, 0, 0}, x[4];
int i;

	/* Set number of rounds to 12 or 16, depending on key length */
	key->rounds = (keybytes <= 10 ? 12 : 16);

	/* Copy key to workspace x */
	for (i = 0; i < 4; i++) {
		x[i] = 0;
		if ((i*4+0) < keybytes) x[i] = (u_int32_t)rawkey[i*4+0] << 24;
		if ((i*4+1) < keybytes) x[i] |= (u_int32_t)rawkey[i*4+1] << 16;
		if ((i*4+2) < keybytes) x[i] |= (u_int32_t)rawkey[i*4+2] << 8;
		if ((i*4+3) < keybytes) x[i] |= (u_int32_t)rawkey[i*4+3];
	}
	/* Generate 32 subkeys, four at a time */
	for (i = 0; i < 32; i+=4) {
		switch (i & 4) {
		 case 0:
			t[0] = z[0] = x[0] ^ cast_sbox5[U_INT8_Tb(x[3])] ^
			 cast_sbox6[U_INT8_Td(x[3])] ^ cast_sbox7[U_INT8_Ta(x[3])] ^
			 cast_sbox8[U_INT8_Tc(x[3])] ^ cast_sbox7[U_INT8_Ta(x[2])];
			t[1] = z[1] = x[2] ^ cast_sbox5[U_INT8_Ta(z[0])] ^
			 cast_sbox6[U_INT8_Tc(z[0])] ^ cast_sbox7[U_INT8_Tb(z[0])] ^
			 cast_sbox8[U_INT8_Td(z[0])] ^ cast_sbox8[U_INT8_Tc(x[2])];
			t[2] = z[2] = x[3] ^ cast_sbox5[U_INT8_Td(z[1])] ^
			 cast_sbox6[U_INT8_Tc(z[1])] ^ cast_sbox7[U_INT8_Tb(z[1])] ^
			 cast_sbox8[U_INT8_Ta(z[1])] ^ cast_sbox5[U_INT8_Tb(x[2])];
			t[3] = z[3] = x[1] ^ cast_sbox5[U_INT8_Tc(z[2])] ^
			 cast_sbox6[U_INT8_Tb(z[2])] ^ cast_sbox7[U_INT8_Td(z[2])] ^
			 cast_sbox8[U_INT8_Ta(z[2])] ^ cast_sbox6[U_INT8_Td(x[2])];
			break;
		 case 4:
			t[0] = x[0] = z[2] ^ cast_sbox5[U_INT8_Tb(z[1])] ^
			 cast_sbox6[U_INT8_Td(z[1])] ^ cast_sbox7[U_INT8_Ta(z[1])] ^
			 cast_sbox8[U_INT8_Tc(z[1])] ^ cast_sbox7[U_INT8_Ta(z[0])];
			t[1] = x[1] = z[0] ^ cast_sbox5[U_INT8_Ta(x[0])] ^
			 cast_sbox6[U_INT8_Tc(x[0])] ^ cast_sbox7[U_INT8_Tb(x[0])] ^
			 cast_sbox8[U_INT8_Td(x[0])] ^ cast_sbox8[U_INT8_Tc(z[0])];
			t[2] = x[2] = z[1] ^ cast_sbox5[U_INT8_Td(x[1])] ^
			 cast_sbox6[U_INT8_Tc(x[1])] ^ cast_sbox7[U_INT8_Tb(x[1])] ^
			 cast_sbox8[U_INT8_Ta(x[1])] ^ cast_sbox5[U_INT8_Tb(z[0])];
			t[3] = x[3] = z[3] ^ cast_sbox5[U_INT8_Tc(x[2])] ^
			 cast_sbox6[U_INT8_Tb(x[2])] ^ cast_sbox7[U_INT8_Td(x[2])] ^
			 cast_sbox8[U_INT8_Ta(x[2])] ^ cast_sbox6[U_INT8_Td(z[0])];
			break;
		}
		switch (i & 12) {
		 case 0:
		 case 12:
			key->xkey[i+0] = cast_sbox5[U_INT8_Ta(t[2])] ^ cast_sbox6[U_INT8_Tb(t[2])] ^
			 cast_sbox7[U_INT8_Td(t[1])] ^ cast_sbox8[U_INT8_Tc(t[1])];
			key->xkey[i+1] = cast_sbox5[U_INT8_Tc(t[2])] ^ cast_sbox6[U_INT8_Td(t[2])] ^
			 cast_sbox7[U_INT8_Tb(t[1])] ^ cast_sbox8[U_INT8_Ta(t[1])];
			key->xkey[i+2] = cast_sbox5[U_INT8_Ta(t[3])] ^ cast_sbox6[U_INT8_Tb(t[3])] ^
			 cast_sbox7[U_INT8_Td(t[0])] ^ cast_sbox8[U_INT8_Tc(t[0])];
			key->xkey[i+3] = cast_sbox5[U_INT8_Tc(t[3])] ^ cast_sbox6[U_INT8_Td(t[3])] ^
			 cast_sbox7[U_INT8_Tb(t[0])] ^ cast_sbox8[U_INT8_Ta(t[0])];
			break;
		 case 4:
		 case 8:
			key->xkey[i+0] = cast_sbox5[U_INT8_Td(t[0])] ^ cast_sbox6[U_INT8_Tc(t[0])] ^
			 cast_sbox7[U_INT8_Ta(t[3])] ^ cast_sbox8[U_INT8_Tb(t[3])];
			key->xkey[i+1] = cast_sbox5[U_INT8_Tb(t[0])] ^ cast_sbox6[U_INT8_Ta(t[0])] ^
			 cast_sbox7[U_INT8_Tc(t[3])] ^ cast_sbox8[U_INT8_Td(t[3])];
			key->xkey[i+2] = cast_sbox5[U_INT8_Td(t[1])] ^ cast_sbox6[U_INT8_Tc(t[1])] ^
			 cast_sbox7[U_INT8_Ta(t[2])] ^ cast_sbox8[U_INT8_Tb(t[2])];
			key->xkey[i+3] = cast_sbox5[U_INT8_Tb(t[1])] ^ cast_sbox6[U_INT8_Ta(t[1])] ^
			 cast_sbox7[U_INT8_Tc(t[2])] ^ cast_sbox8[U_INT8_Td(t[2])];
			break;
		}
		switch (i & 12) {
		 case 0:
			key->xkey[i+0] ^= cast_sbox5[U_INT8_Tc(z[0])];
			key->xkey[i+1] ^= cast_sbox6[U_INT8_Tc(z[1])];
			key->xkey[i+2] ^= cast_sbox7[U_INT8_Tb(z[2])];
			key->xkey[i+3] ^= cast_sbox8[U_INT8_Ta(z[3])];
			break;
		 case 4:
			key->xkey[i+0] ^= cast_sbox5[U_INT8_Ta(x[2])];
			key->xkey[i+1] ^= cast_sbox6[U_INT8_Tb(x[3])];
			key->xkey[i+2] ^= cast_sbox7[U_INT8_Td(x[0])];
			key->xkey[i+3] ^= cast_sbox8[U_INT8_Td(x[1])];
			break;
		 case 8:
			key->xkey[i+0] ^= cast_sbox5[U_INT8_Tb(z[2])];
			key->xkey[i+1] ^= cast_sbox6[U_INT8_Ta(z[3])];
			key->xkey[i+2] ^= cast_sbox7[U_INT8_Tc(z[0])];
			key->xkey[i+3] ^= cast_sbox8[U_INT8_Tc(z[1])];
			break;
		 case 12:
			key->xkey[i+0] ^= cast_sbox5[U_INT8_Td(x[0])];
			key->xkey[i+1] ^= cast_sbox6[U_INT8_Td(x[1])];
			key->xkey[i+2] ^= cast_sbox7[U_INT8_Ta(x[2])];
			key->xkey[i+3] ^= cast_sbox8[U_INT8_Tb(x[3])];
			break;
		}
		if (i >= 16) {
			key->xkey[i+0] &= 31;
			key->xkey[i+1] &= 31;
			key->xkey[i+2] &= 31;
			key->xkey[i+3] &= 31;
		}
	}
	/* Wipe clean */
	for (i = 0; i < 4; i++) {
		t[i] = x[i] = z[i] = 0;
	}
}