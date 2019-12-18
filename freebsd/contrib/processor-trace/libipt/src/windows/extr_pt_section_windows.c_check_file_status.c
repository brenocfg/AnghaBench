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
struct pt_section {struct pt_sec_windows_status* status; } ;
struct TYPE_2__ {scalar_t__ st_size; scalar_t__ st_mtime; } ;
struct pt_sec_windows_status {TYPE_1__ stat; } ;
struct _stat {scalar_t__ st_size; scalar_t__ st_mtime; } ;

/* Variables and functions */
 int _fstat (int,struct _stat*) ; 
 int pte_bad_file ; 
 int pte_bad_image ; 
 int pte_internal ; 

__attribute__((used)) static int check_file_status(struct pt_section *section, int fd)
{
	struct pt_sec_windows_status *status;
	struct _stat stat;
	int errcode;

	if (!section)
		return -pte_internal;

	errcode = _fstat(fd, &stat);
	if (errcode)
		return -pte_bad_file;

	status = section->status;
	if (!status)
		return -pte_internal;

	if (stat.st_size != status->stat.st_size)
		return -pte_bad_image;

	if (stat.st_mtime != status->stat.st_mtime)
		return -pte_bad_image;

	return 0;
}