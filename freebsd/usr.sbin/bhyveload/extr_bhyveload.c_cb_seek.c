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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
struct cb_file {TYPE_1__ cf_u; scalar_t__ cf_isdir; } ;

/* Variables and functions */
 int EINVAL ; 
 int errno ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cb_seek(void *arg, void *h, uint64_t offset, int whence)
{
	struct cb_file *cf = h;

	if (cf->cf_isdir)
		return (EINVAL);
	if (lseek(cf->cf_u.fd, offset, whence) < 0)
		return (errno);
	return (0);
}