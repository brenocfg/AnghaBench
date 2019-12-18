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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct archive_read {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  read_u32 (struct archive_read*,scalar_t__*) ; 
 int /*<<< orphan*/  read_u64 (struct archive_read*,scalar_t__*) ; 
 scalar_t__ time_win_to_unix (scalar_t__) ; 

__attribute__((used)) static int parse_htime_item(struct archive_read* a, char unix_time,
    uint64_t* where, ssize_t* extra_data_size)
{
	if(unix_time) {
		uint32_t time_val;
		if(!read_u32(a, &time_val))
			return ARCHIVE_EOF;

		*extra_data_size -= 4;
		*where = (uint64_t) time_val;
	} else {
		uint64_t windows_time;
		if(!read_u64(a, &windows_time))
			return ARCHIVE_EOF;

		*where = time_win_to_unix(windows_time);
		*extra_data_size -= 8;
	}

	return ARCHIVE_OK;
}