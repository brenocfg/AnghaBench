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
typedef  int /*<<< orphan*/  uint32_t ;
struct hashfile {int dummy; } ;
typedef  int /*<<< orphan*/  byte_values ;

/* Variables and functions */
 unsigned char MIDX_HASH_VERSION ; 
 size_t MIDX_HEADER_SIZE ; 
 int /*<<< orphan*/  MIDX_SIGNATURE ; 
 unsigned char MIDX_VERSION ; 
 int /*<<< orphan*/  hashwrite (struct hashfile*,unsigned char*,int) ; 
 int /*<<< orphan*/  hashwrite_be32 (struct hashfile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t write_midx_header(struct hashfile *f,
				unsigned char num_chunks,
				uint32_t num_packs)
{
	unsigned char byte_values[4];

	hashwrite_be32(f, MIDX_SIGNATURE);
	byte_values[0] = MIDX_VERSION;
	byte_values[1] = MIDX_HASH_VERSION;
	byte_values[2] = num_chunks;
	byte_values[3] = 0; /* unused */
	hashwrite(f, byte_values, sizeof(byte_values));
	hashwrite_be32(f, num_packs);

	return MIDX_HEADER_SIZE;
}