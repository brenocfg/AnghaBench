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
struct hws_lsctl_request_block {int dummy; } ;
typedef  int /*<<< orphan*/  sreq ;

/* Variables and functions */
 int lsctl (struct hws_lsctl_request_block*) ; 
 int /*<<< orphan*/  memset (struct hws_lsctl_request_block*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sf_disable(void)
{
	struct hws_lsctl_request_block sreq;

	memset(&sreq, 0, sizeof(sreq));
	return lsctl(&sreq);
}