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
struct TYPE_6__ {unsigned char* next_out; int avail_out; unsigned char* next_in; unsigned long avail_in; unsigned long total_out; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 int /*<<< orphan*/  Z_FINISH ; 
 scalar_t__ Z_OK ; 
 scalar_t__ git_deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int git_deflate_bound (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  git_deflate_end (TYPE_1__*) ; 
 int /*<<< orphan*/  git_deflate_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned char* xmalloc (int) ; 
 int /*<<< orphan*/  zlib_compression_level ; 

__attribute__((used)) static unsigned char *deflate_it(char *data,
				 unsigned long size,
				 unsigned long *result_size)
{
	int bound;
	unsigned char *deflated;
	git_zstream stream;

	git_deflate_init(&stream, zlib_compression_level);
	bound = git_deflate_bound(&stream, size);
	deflated = xmalloc(bound);
	stream.next_out = deflated;
	stream.avail_out = bound;

	stream.next_in = (unsigned char *)data;
	stream.avail_in = size;
	while (git_deflate(&stream, Z_FINISH) == Z_OK)
		; /* nothing */
	git_deflate_end(&stream);
	*result_size = stream.total_out;
	return deflated;
}