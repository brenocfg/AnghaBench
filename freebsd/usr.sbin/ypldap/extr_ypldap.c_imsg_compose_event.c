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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct imsgev {int /*<<< orphan*/  ibuf; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int imsg_compose (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imsg_event_add (struct imsgev*) ; 

int
imsg_compose_event(struct imsgev *iev, u_int16_t type, u_int32_t peerid,
    pid_t pid, int fd, void *data, u_int16_t datalen)
{
	int	ret;

	if ((ret = imsg_compose(&iev->ibuf, type, peerid,
	    pid, fd, data, datalen)) != -1)
		imsg_event_add(iev);
	return (ret);
}