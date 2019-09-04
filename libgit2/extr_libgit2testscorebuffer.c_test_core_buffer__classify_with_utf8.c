#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* ptr; size_t size; size_t asize; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int git_buf_text_contains_nul (TYPE_1__*) ; 
 int git_buf_text_is_binary (TYPE_1__*) ; 

void test_core_buffer__classify_with_utf8(void)
{
	char *data0 = "Simple text\n";
	size_t data0len = 12;
	char *data1 = "Is that UTF-8 data I see…\nYep!\n";
	size_t data1len = 31;
	char *data2 = "Internal NUL!!!\000\n\nI see you!\n";
	size_t data2len = 29;
	char *data3 = "\xef\xbb\xbfThis is UTF-8 with a BOM.\n";
	size_t data3len = 20;
	git_buf b;

	b.ptr = data0; b.size = b.asize = data0len;
	cl_assert(!git_buf_text_is_binary(&b));
	cl_assert(!git_buf_text_contains_nul(&b));

	b.ptr = data1; b.size = b.asize = data1len;
	cl_assert(!git_buf_text_is_binary(&b));
	cl_assert(!git_buf_text_contains_nul(&b));

	b.ptr = data2; b.size = b.asize = data2len;
	cl_assert(git_buf_text_is_binary(&b));
	cl_assert(git_buf_text_contains_nul(&b));

	b.ptr = data3; b.size = b.asize = data3len;
	cl_assert(!git_buf_text_is_binary(&b));
	cl_assert(!git_buf_text_contains_nul(&b));
}