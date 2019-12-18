#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_6__ {int* innerHash; int* keyBuffer; } ;
typedef  TYPE_1__ sha1nfo ;

/* Variables and functions */
 size_t BLOCK_LENGTH ; 
 size_t HASH_LENGTH ; 
 int HMAC_OPAD ; 
 int /*<<< orphan*/  memcpy (int*,size_t const*,size_t) ; 
 size_t const* sha1_final (TYPE_1__*) ; 
 int /*<<< orphan*/  sha1_init (TYPE_1__*) ; 
 int /*<<< orphan*/  sha1_write1 (TYPE_1__*,int) ; 

const uint8_t *sha1_final_hmac(sha1nfo *s)
{
	uint8_t i;
	memcpy(s->innerHash, sha1_final(s), HASH_LENGTH);
	sha1_init(s);
	for (i = 0; i < BLOCK_LENGTH; ++i) sha1_write1(s, s->keyBuffer[i] ^ HMAC_OPAD);
	for (i = 0; i < HASH_LENGTH; ++i) sha1_write1(s, s->innerHash[i]);
	return sha1_final(s);
}