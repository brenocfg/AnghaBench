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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/ * PADLOCK_ALIGN (int /*<<< orphan*/ *) ; 
 int SHA1_HASH_LEN ; 
 int /*<<< orphan*/  padlock_output_block (int*,int*,int) ; 

__attribute__((used)) static void
padlock_do_sha1(const u_char *in, u_char *out, int count)
{
	u_char buf[128+16];	/* PadLock needs at least 128 bytes buffer. */
	u_char *result = PADLOCK_ALIGN(buf);

	((uint32_t *)result)[0] = 0x67452301;
	((uint32_t *)result)[1] = 0xEFCDAB89;
	((uint32_t *)result)[2] = 0x98BADCFE;
	((uint32_t *)result)[3] = 0x10325476;
	((uint32_t *)result)[4] = 0xC3D2E1F0;

#ifdef __GNUCLIKE_ASM
	__asm __volatile(
		".byte  0xf3, 0x0f, 0xa6, 0xc8" /* rep xsha1 */
			: "+S"(in), "+D"(result)
			: "c"(count), "a"(0)
		);
#endif

	padlock_output_block((uint32_t *)result, (uint32_t *)out,
	    SHA1_HASH_LEN / sizeof(uint32_t));
}