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
struct uni_msg {size_t b_wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,size_t,size_t) ; 
 int uni_msg_ensure (struct uni_msg*,size_t) ; 

int
uni_msg_append(struct uni_msg *m, void *buf, size_t size)
{
	int error;

	if ((error = uni_msg_ensure(m, size)))
		return (error);
	bcopy(buf, m->b_wptr, size);
	m->b_wptr += size;

	return (0);
}