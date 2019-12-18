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
typedef  int /*<<< orphan*/  ldns_sha1_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_sha1_final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_sha1_update (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 

unsigned char *
ldns_sha1(unsigned char *data, unsigned int data_len, unsigned char *digest)
{
    ldns_sha1_ctx ctx;
    ldns_sha1_init(&ctx);
    ldns_sha1_update(&ctx, data, data_len);
    ldns_sha1_final(digest, &ctx);
    return digest;
}