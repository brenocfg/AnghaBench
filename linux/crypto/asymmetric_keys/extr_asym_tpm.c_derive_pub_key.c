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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int /*<<< orphan*/  SETKEY_PARAMS_SIZE ; 
 int definite_length (int) ; 
 int* encode_tag_length (int*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t derive_pub_key(const void *pub_key, uint32_t len, uint8_t *buf)
{
	uint8_t *cur = buf;
	uint32_t n_len = definite_length(len) + 1 + len + 1;
	uint32_t e_len = definite_length(3) + 1 + 3;
	uint8_t e[3] = { 0x01, 0x00, 0x01 };

	/* SEQUENCE */
	cur = encode_tag_length(cur, 0x30, n_len + e_len);
	/* INTEGER n */
	cur = encode_tag_length(cur, 0x02, len + 1);
	cur[0] = 0x00;
	memcpy(cur + 1, pub_key, len);
	cur += len + 1;
	cur = encode_tag_length(cur, 0x02, sizeof(e));
	memcpy(cur, e, sizeof(e));
	cur += sizeof(e);
	/* Zero parameters to satisfy set_pub_key ABI. */
	memset(cur, 0, SETKEY_PARAMS_SIZE);

	return cur - buf;
}