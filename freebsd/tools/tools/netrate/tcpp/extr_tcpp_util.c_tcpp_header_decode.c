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
struct tcpp_header {int /*<<< orphan*/  th_len; int /*<<< orphan*/  th_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 

void
tcpp_header_decode(struct tcpp_header *thp)
{

	thp->th_magic = be32toh(thp->th_magic);
	thp->th_len = be64toh(thp->th_len);
}