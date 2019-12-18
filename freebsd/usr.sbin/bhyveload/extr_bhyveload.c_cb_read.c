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
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
struct cb_file {TYPE_1__ cf_u; scalar_t__ cf_isdir; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t read (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int
cb_read(void *arg, void *h, void *buf, size_t size, size_t *resid)
{
	struct cb_file *cf = h;
	ssize_t sz;

	if (cf->cf_isdir)
		return (EINVAL);
	sz = read(cf->cf_u.fd, buf, size);
	if (sz < 0)
		return (EINVAL);
	*resid = size - sz;
	return (0);
}