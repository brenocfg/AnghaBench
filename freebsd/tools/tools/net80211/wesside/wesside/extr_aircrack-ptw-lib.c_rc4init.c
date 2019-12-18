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
typedef  int uint8_t ;
struct TYPE_3__ {int* s; int /*<<< orphan*/  j; int /*<<< orphan*/  i; } ;
typedef  TYPE_1__ rc4state ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int n ; 
 int /*<<< orphan*/  rc4initial ; 

__attribute__((used)) static void rc4init ( uint8_t * key, int keylen, rc4state * state) {
	int i;
	int j;
	uint8_t tmp;
	memcpy(state->s, &rc4initial, n);
	j = 0;
	for (i = 0; i < n; i++) {
		j = (j + state->s[i] + key[i % keylen]) % n;
		tmp = state->s[i];
		state->s[i] = state->s[j];
		state->s[j] = tmp;
	}
	state->i = 0;
	state->j = 0;
}