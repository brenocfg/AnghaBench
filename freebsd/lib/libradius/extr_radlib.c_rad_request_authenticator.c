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
struct rad_handle {scalar_t__ out; } ;
typedef  int ssize_t ;

/* Variables and functions */
 size_t LEN_AUTH ; 
 scalar_t__ POS_AUTH ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t) ; 

ssize_t
rad_request_authenticator(struct rad_handle *h, char *buf, size_t len)
{
	if (len < LEN_AUTH)
		return (-1);
	memcpy(buf, h->out + POS_AUTH, LEN_AUTH);
	if (len > LEN_AUTH)
		buf[LEN_AUTH] = '\0';
	return (LEN_AUTH);
}