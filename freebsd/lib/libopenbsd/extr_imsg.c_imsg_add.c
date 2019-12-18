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
typedef  int u_int16_t ;
struct ibuf {int dummy; } ;

/* Variables and functions */
 int ibuf_add (struct ibuf*,void const*,int) ; 
 int /*<<< orphan*/  ibuf_free (struct ibuf*) ; 

int
imsg_add(struct ibuf *msg, const void *data, u_int16_t datalen)
{
	if (datalen)
		if (ibuf_add(msg, data, datalen) == -1) {
			ibuf_free(msg);
			return (-1);
		}
	return (datalen);
}