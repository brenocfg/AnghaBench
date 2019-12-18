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
struct ioc_read_toc_entry {int data_len; int /*<<< orphan*/  data; scalar_t__ starting_track; int /*<<< orphan*/  address_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDIOREADTOCENTRYS ; 
 int /*<<< orphan*/  CD_LBA_FORMAT ; 
 int /*<<< orphan*/  CD_MSF_FORMAT ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ msf ; 
 int /*<<< orphan*/  toc_buffer ; 

__attribute__((used)) static int
read_toc_entrys(int len)
{
	struct ioc_read_toc_entry t;

	t.address_format = msf ? CD_MSF_FORMAT : CD_LBA_FORMAT;
	t.starting_track = 0;
	t.data_len = len;
	t.data = toc_buffer;

	return (ioctl (fd, CDIOREADTOCENTRYS, (char *) &t));
}