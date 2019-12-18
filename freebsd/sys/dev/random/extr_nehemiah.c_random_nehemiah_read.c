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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t u_int ;

/* Variables and functions */
 int /*<<< orphan*/  FPU_KERN_NORMAL ; 
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  VIA_RNG_store (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fpu_ctx_save ; 
 int /*<<< orphan*/  fpu_kern_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpu_kern_leave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static u_int
random_nehemiah_read(void *buf, u_int c)
{
	uint8_t *b;
	size_t count, ret;
	uint64_t tmp;

	fpu_kern_enter(curthread, fpu_ctx_save, FPU_KERN_NORMAL);
	b = buf;
	for (count = c; count > 0; count -= ret) {
		ret = MIN(VIA_RNG_store(&tmp), count);
		memcpy(b, &tmp, ret);
		b += ret;
	}
	fpu_kern_leave(curthread, fpu_ctx_save);

	return (c);
}