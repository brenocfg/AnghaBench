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
struct tentry_info {scalar_t__ paddr; } ;
struct ta_buf_ifidx {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IF_NAMESIZE ; 
 scalar_t__ strnlen (char*,scalar_t__) ; 

__attribute__((used)) static int
ta_prepare_del_ifidx(struct ip_fw_chain *ch, struct tentry_info *tei,
    void *ta_buf)
{
	struct ta_buf_ifidx *tb;
	char *ifname;

	tb = (struct ta_buf_ifidx *)ta_buf;

	/* Check if string is terminated */
	ifname = (char *)tei->paddr;
	if (strnlen(ifname, IF_NAMESIZE) == IF_NAMESIZE)
		return (EINVAL);

	return (0);
}