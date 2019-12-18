#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  file_pair ;
struct TYPE_2__ {scalar_t__ avail_in; int /*<<< orphan*/  total_in; int /*<<< orphan*/  total_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_BUFFER_SIZE ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  in_buf ; 
 scalar_t__ io_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ io_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  message_progress_update () ; 
 TYPE_1__ strm ; 
 scalar_t__ user_abort ; 

__attribute__((used)) static bool
coder_passthru(file_pair *pair)
{
	while (strm.avail_in != 0) {
		if (user_abort)
			return false;

		if (io_write(pair, &in_buf, strm.avail_in))
			return false;

		strm.total_in += strm.avail_in;
		strm.total_out = strm.total_in;
		message_progress_update();

		strm.avail_in = io_read(pair, &in_buf, IO_BUFFER_SIZE);
		if (strm.avail_in == SIZE_MAX)
			return false;
	}

	return true;
}