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
struct cubic {int /*<<< orphan*/  max_cwnd; } ;
struct cc_var {struct cubic* cc_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV (struct cc_var*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cwnd ; 

__attribute__((used)) static void
cubic_conn_init(struct cc_var *ccv)
{
	struct cubic *cubic_data;

	cubic_data = ccv->cc_data;

	/*
	 * Ensure we have a sane initial value for max_cwnd recorded. Without
	 * this here bad things happen when entries from the TCP hostcache
	 * get used.
	 */
	cubic_data->max_cwnd = CCV(ccv, snd_cwnd);
}