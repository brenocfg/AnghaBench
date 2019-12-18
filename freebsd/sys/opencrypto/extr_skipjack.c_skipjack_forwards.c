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
typedef  int u_int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  g0 (int,int,int,int) ; 
 int /*<<< orphan*/  g2 (int,int,int,int) ; 
 int /*<<< orphan*/  g4 (int,int,int,int) ; 
 int /*<<< orphan*/  g6 (int,int,int,int) ; 
 int /*<<< orphan*/  g8 (int,int,int,int) ; 

void
skipjack_forwards(u_int8_t *plain, u_int8_t *cipher, u_int8_t **key_tables)
{
	u_int8_t wh1 = plain[0];  u_int8_t wl1 = plain[1];
	u_int8_t wh2 = plain[2];  u_int8_t wl2 = plain[3];
	u_int8_t wh3 = plain[4];  u_int8_t wl3 = plain[5];
	u_int8_t wh4 = plain[6];  u_int8_t wl4 = plain[7];

	u_int8_t * k0 = key_tables [0];
	u_int8_t * k1 = key_tables [1];
	u_int8_t * k2 = key_tables [2];
	u_int8_t * k3 = key_tables [3];
	u_int8_t * k4 = key_tables [4];
	u_int8_t * k5 = key_tables [5];
	u_int8_t * k6 = key_tables [6];
	u_int8_t * k7 = key_tables [7];
	u_int8_t * k8 = key_tables [8];
	u_int8_t * k9 = key_tables [9];

	/* first 8 rounds */
	g0 (wh1,wl1, wh1,wl1); wl4 ^= wl1 ^ 1; wh4 ^= wh1;
	g4 (wh4,wl4, wh4,wl4); wl3 ^= wl4 ^ 2; wh3 ^= wh4;
	g8 (wh3,wl3, wh3,wl3); wl2 ^= wl3 ^ 3; wh2 ^= wh3;
	g2 (wh2,wl2, wh2,wl2); wl1 ^= wl2 ^ 4; wh1 ^= wh2;
	g6 (wh1,wl1, wh1,wl1); wl4 ^= wl1 ^ 5; wh4 ^= wh1;
	g0 (wh4,wl4, wh4,wl4); wl3 ^= wl4 ^ 6; wh3 ^= wh4;
	g4 (wh3,wl3, wh3,wl3); wl2 ^= wl3 ^ 7; wh2 ^= wh3;
	g8 (wh2,wl2, wh2,wl2); wl1 ^= wl2 ^ 8; wh1 ^= wh2;

	/* second 8 rounds */
	wh2 ^= wh1; wl2 ^= wl1 ^ 9 ; g2 (wh1,wl1, wh1,wl1);
	wh1 ^= wh4; wl1 ^= wl4 ^ 10; g6 (wh4,wl4, wh4,wl4);
	wh4 ^= wh3; wl4 ^= wl3 ^ 11; g0 (wh3,wl3, wh3,wl3);
	wh3 ^= wh2; wl3 ^= wl2 ^ 12; g4 (wh2,wl2, wh2,wl2);
	wh2 ^= wh1; wl2 ^= wl1 ^ 13; g8 (wh1,wl1, wh1,wl1);
	wh1 ^= wh4; wl1 ^= wl4 ^ 14; g2 (wh4,wl4, wh4,wl4);
	wh4 ^= wh3; wl4 ^= wl3 ^ 15; g6 (wh3,wl3, wh3,wl3);
	wh3 ^= wh2; wl3 ^= wl2 ^ 16; g0 (wh2,wl2, wh2,wl2);

	/* third 8 rounds */
	g4 (wh1,wl1, wh1,wl1); wl4 ^= wl1 ^ 17; wh4 ^= wh1;
	g8 (wh4,wl4, wh4,wl4); wl3 ^= wl4 ^ 18; wh3 ^= wh4;
	g2 (wh3,wl3, wh3,wl3); wl2 ^= wl3 ^ 19; wh2 ^= wh3;
	g6 (wh2,wl2, wh2,wl2); wl1 ^= wl2 ^ 20; wh1 ^= wh2;
	g0 (wh1,wl1, wh1,wl1); wl4 ^= wl1 ^ 21; wh4 ^= wh1;
	g4 (wh4,wl4, wh4,wl4); wl3 ^= wl4 ^ 22; wh3 ^= wh4;
	g8 (wh3,wl3, wh3,wl3); wl2 ^= wl3 ^ 23; wh2 ^= wh3;
	g2 (wh2,wl2, wh2,wl2); wl1 ^= wl2 ^ 24; wh1 ^= wh2;

	/* last 8 rounds */
	wh2 ^= wh1; wl2 ^= wl1 ^ 25; g6 (wh1,wl1, wh1,wl1);
	wh1 ^= wh4; wl1 ^= wl4 ^ 26; g0 (wh4,wl4, wh4,wl4);
	wh4 ^= wh3; wl4 ^= wl3 ^ 27; g4 (wh3,wl3, wh3,wl3);
	wh3 ^= wh2; wl3 ^= wl2 ^ 28; g8 (wh2,wl2, wh2,wl2);
	wh2 ^= wh1; wl2 ^= wl1 ^ 29; g2 (wh1,wl1, wh1,wl1);
	wh1 ^= wh4; wl1 ^= wl4 ^ 30; g6 (wh4,wl4, wh4,wl4);
	wh4 ^= wh3; wl4 ^= wl3 ^ 31; g0 (wh3,wl3, wh3,wl3);
	wh3 ^= wh2; wl3 ^= wl2 ^ 32; g4 (wh2,wl2, wh2,wl2);

	/* pack into byte vector */
	cipher [0] = wh1;  cipher [1] = wl1;
	cipher [2] = wh2;  cipher [3] = wl2;
	cipher [4] = wh3;  cipher [5] = wl3;
	cipher [6] = wh4;  cipher [7] = wl4;
}