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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u_int ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  dst ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (struct in_addr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rss_hash (size_t,int /*<<< orphan*/ *) ; 

uint32_t
rss_hash_ip4_2tuple(struct in_addr src, struct in_addr dst)
{
	uint8_t data[sizeof(src) + sizeof(dst)];
	u_int datalen;

	datalen = 0;
	bcopy(&src, &data[datalen], sizeof(src));
	datalen += sizeof(src);
	bcopy(&dst, &data[datalen], sizeof(dst));
	datalen += sizeof(dst);
	return (rss_hash(datalen, data));
}