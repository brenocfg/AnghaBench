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
typedef  int uint32_t ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdceem_m_crc32_cb ; 
 int m_apply (struct mbuf*,int,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static uint32_t
cdceem_m_crc32(struct mbuf *m, uint32_t src_offset, uint32_t src_len)
{
	uint32_t crc = 0xFFFFFFFF;
	int error;

	error = m_apply(m, src_offset, src_len, cdceem_m_crc32_cb, &crc);
	return (crc ^ 0xFFFFFFFF);
}