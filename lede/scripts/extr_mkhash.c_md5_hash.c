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
typedef  int /*<<< orphan*/  MD5_CTX ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  MD5_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_end (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_hash (void*,int,int /*<<< orphan*/ *) ; 
 void* hash_buf (int /*<<< orphan*/ *,int*) ; 
 char const* hash_string (unsigned char*,int) ; 

__attribute__((used)) static const char *md5_hash(FILE *f)
{
	MD5_CTX ctx;
	unsigned char val[MD5_DIGEST_LENGTH];
	void *buf;
	int len;

	MD5_begin(&ctx);
	while ((buf = hash_buf(f, &len)) != NULL)
		MD5_hash(buf, len, &ctx);
	MD5_end(val, &ctx);

	return hash_string(val, MD5_DIGEST_LENGTH);
}