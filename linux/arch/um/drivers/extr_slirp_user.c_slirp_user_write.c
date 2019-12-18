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
struct slirp_data {int /*<<< orphan*/  slip; } ;

/* Variables and functions */
 int slip_proto_write (int,void*,int,int /*<<< orphan*/ *) ; 

int slirp_user_write(int fd, void *buf, int len, struct slirp_data *pri)
{
	return slip_proto_write(fd, buf, len, &pri->slip);
}