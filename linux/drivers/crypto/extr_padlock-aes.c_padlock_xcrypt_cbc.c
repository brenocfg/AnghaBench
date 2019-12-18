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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/ * cbc_crypt (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,void*,int) ; 
 int cbc_fetch_blocks ; 

__attribute__((used)) static inline u8 *padlock_xcrypt_cbc(const u8 *input, u8 *output, void *key,
				     u8 *iv, void *control_word, u32 count)
{
	u32 initial = count & (cbc_fetch_blocks - 1);

	if (count < cbc_fetch_blocks)
		return cbc_crypt(input, output, key, iv, control_word, count);

	count -= initial;

	if (initial)
		asm volatile (".byte 0xf3,0x0f,0xa7,0xd0"	/* rep xcryptcbc */
			      : "+S" (input), "+D" (output), "+a" (iv)
			      : "d" (control_word), "b" (key), "c" (initial));

	asm volatile (".byte 0xf3,0x0f,0xa7,0xd0"	/* rep xcryptcbc */
		      : "+S" (input), "+D" (output), "+a" (iv)
		      : "d" (control_word), "b" (key), "c" (count));
	return iv;
}