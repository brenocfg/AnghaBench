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
struct swrap_file_hdr {int magic; int version_major; int version_minor; int timezone; int sigfigs; int link_type; int /*<<< orphan*/  frame_max_len; } ;
typedef  int /*<<< orphan*/  file_hdr ;

/* Variables and functions */
 int O_APPEND ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SWRAP_FRAME_LENGTH_MAX ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  write (int,struct swrap_file_hdr*,int) ; 

__attribute__((used)) static int swrap_get_pcap_fd(const char *fname)
{
	static int fd = -1;

	if (fd != -1) return fd;

	fd = open(fname, O_WRONLY|O_CREAT|O_EXCL|O_APPEND, 0644);
	if (fd != -1) {
		struct swrap_file_hdr file_hdr;
		file_hdr.magic		= 0xA1B2C3D4;
		file_hdr.version_major	= 0x0002;
		file_hdr.version_minor	= 0x0004;
		file_hdr.timezone	= 0x00000000;
		file_hdr.sigfigs	= 0x00000000;
		file_hdr.frame_max_len	= SWRAP_FRAME_LENGTH_MAX;
		file_hdr.link_type	= 0x0065; /* 101 RAW IP */

		write(fd, &file_hdr, sizeof(file_hdr));
		return fd;
	}

	fd = open(fname, O_WRONLY|O_APPEND, 0644);

	return fd;
}