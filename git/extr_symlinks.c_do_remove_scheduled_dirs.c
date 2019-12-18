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
struct TYPE_2__ {int len; char* buf; } ;

/* Variables and functions */
 TYPE_1__ removal ; 
 scalar_t__ rmdir (char*) ; 

__attribute__((used)) static void do_remove_scheduled_dirs(int new_len)
{
	while (removal.len > new_len) {
		removal.buf[removal.len] = '\0';
		if (rmdir(removal.buf))
			break;
		do {
			removal.len--;
		} while (removal.len > new_len &&
			 removal.buf[removal.len] != '/');
	}
	removal.len = new_len;
}