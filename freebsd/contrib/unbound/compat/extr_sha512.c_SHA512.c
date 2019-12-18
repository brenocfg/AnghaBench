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
typedef  int /*<<< orphan*/  SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA512_Update (int /*<<< orphan*/ *,void*,unsigned int) ; 

unsigned char *
SHA512(void *data, unsigned int data_len, unsigned char *digest)
{
    SHA512_CTX ctx;
    SHA512_Init(&ctx);
    SHA512_Update(&ctx, data, data_len);
    SHA512_Final(digest, &ctx);
    return digest;
}