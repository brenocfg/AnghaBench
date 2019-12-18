#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {size_t key; } ;

/* Variables and functions */
 int KEY_LEN ; 
 TYPE_1__* board ; 
 int /*<<< orphan*/ ** key ; 

__attribute__((used)) static void xor_fw(uint8_t *data, int len)
{
	int i;

	for (i = 0; i <= len; i++) {
		data[i] ^= key[board->key][i % KEY_LEN];
	}
}