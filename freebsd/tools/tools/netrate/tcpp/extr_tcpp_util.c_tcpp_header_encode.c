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
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe64 (int /*<<< orphan*/ ) ; 

void
tcpp_header_encode(struct tcpp_header *thp)
{

	thp->th_magic = htobe32(thp->th_magic);
	thp->th_len = htobe64(thp->th_len);
}