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
typedef  int u8 ;

/* Variables and functions */
 size_t AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void pad_block(u8 *pad, const u8 *addr, size_t len)
{
	os_memset(pad, 0, AES_BLOCK_SIZE);
	os_memcpy(pad, addr, len);

	if (len < AES_BLOCK_SIZE)
		pad[len] = 0x80;
}