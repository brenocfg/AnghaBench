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
typedef  int uint32_t ;

/* Variables and functions */
 char* PADLOCK_ALIGN (char*) ; 
 int SHA2_256_HASH_LEN ; 
 int /*<<< orphan*/  padlock_output_block (int*,int*,int) ; 

__attribute__((used)) static void
padlock_do_sha256(const char *in, char *out, int count)
{
	char buf[128+16];	/* PadLock needs at least 128 bytes buffer. */
	char *result = PADLOCK_ALIGN(buf);

	((uint32_t *)result)[0] = 0x6A09E667;
	((uint32_t *)result)[1] = 0xBB67AE85;
	((uint32_t *)result)[2] = 0x3C6EF372;
	((uint32_t *)result)[3] = 0xA54FF53A;
	((uint32_t *)result)[4] = 0x510E527F;
	((uint32_t *)result)[5] = 0x9B05688C;
	((uint32_t *)result)[6] = 0x1F83D9AB;
	((uint32_t *)result)[7] = 0x5BE0CD19;

#ifdef __GNUCLIKE_ASM
	__asm __volatile(
		".byte  0xf3, 0x0f, 0xa6, 0xd0" /* rep xsha256 */
			: "+S"(in), "+D"(result)
			: "c"(count), "a"(0)
		);
#endif

	padlock_output_block((uint32_t *)result, (uint32_t *)out,
	    SHA2_256_HASH_LEN / sizeof(uint32_t));
}