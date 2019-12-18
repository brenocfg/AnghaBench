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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int SIZE_IN_WORDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void mtk_aes_write_state_le(__le32 *dst, const u32 *src, u32 size)
{
	int i;

	for (i = 0; i < SIZE_IN_WORDS(size); i++)
		dst[i] = cpu_to_le32(src[i]);
}