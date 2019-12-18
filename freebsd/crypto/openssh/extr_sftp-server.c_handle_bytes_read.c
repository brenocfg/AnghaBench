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
typedef  int /*<<< orphan*/  u_int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  bytes_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLE_FILE ; 
 scalar_t__ handle_is_ok (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* handles ; 

__attribute__((used)) static u_int64_t
handle_bytes_read(int handle)
{
	if (handle_is_ok(handle, HANDLE_FILE))
		return (handles[handle].bytes_read);
	return 0;
}