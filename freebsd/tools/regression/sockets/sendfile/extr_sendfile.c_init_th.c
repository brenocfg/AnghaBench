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
struct test_header {int /*<<< orphan*/  th_md5; void* th_length; void* th_offset; void* th_header_length; void* th_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD5FileChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_MAGIC ; 
 int /*<<< orphan*/  bzero (struct test_header*,int) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path ; 

__attribute__((used)) static void
init_th(struct test_header *th, uint32_t header_length, uint32_t offset, 
		uint32_t length)
{
	bzero(th, sizeof(*th));
	th->th_magic = htonl(TEST_MAGIC);
	th->th_header_length = htonl(header_length);
	th->th_offset = htonl(offset);
	th->th_length = htonl(length);

	MD5FileChunk(path, th->th_md5, offset, length);
}