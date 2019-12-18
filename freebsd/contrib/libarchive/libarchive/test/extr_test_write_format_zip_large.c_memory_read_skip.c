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
struct fileblocks {scalar_t__ fileposition; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ memory_read_seek (struct archive*,void*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t
memory_read_skip(struct archive *a, void *_private, int64_t skip)
{
	struct fileblocks *private = _private;
	int64_t old_position = private->fileposition;
	int64_t new_position = memory_read_seek(a, _private, skip, SEEK_CUR);
	return (new_position - old_position);
}