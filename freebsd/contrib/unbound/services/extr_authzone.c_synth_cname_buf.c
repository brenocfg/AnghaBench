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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static size_t
synth_cname_buf(uint8_t* qname, size_t qname_len, size_t dname_len,
	uint8_t* dtarg, size_t dtarglen, uint8_t* buf, size_t buflen)
{
	size_t newlen = qname_len + dtarglen - dname_len;
	if(newlen > buflen) {
		/* YXDOMAIN error */
		return 0;
	}
	/* new name is concatenation of qname front (without DNAME owner)
	 * and DNAME target name */
	memcpy(buf, qname, qname_len-dname_len);
	memmove(buf+(qname_len-dname_len), dtarg, dtarglen);
	return newlen;
}