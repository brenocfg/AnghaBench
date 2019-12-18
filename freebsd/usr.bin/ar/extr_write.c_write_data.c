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
struct bsdar {int dummy; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  archive_errno (struct archive*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 scalar_t__ archive_write_data (struct archive*,void const*,size_t) ; 
 int /*<<< orphan*/  bsdar_errc (struct bsdar*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefault_buffer (void const*,size_t) ; 

__attribute__((used)) static void
write_data(struct bsdar *bsdar, struct archive *a, const void *buf, size_t s)
{
	ssize_t written;

	prefault_buffer(buf, s);
	while (s > 0) {
		written = archive_write_data(a, buf, s);
		if (written < 0)
			bsdar_errc(bsdar, EX_SOFTWARE, archive_errno(a), "%s",
			    archive_error_string(a));
		buf = (const char *)buf + written;
		s -= written;
	}
}