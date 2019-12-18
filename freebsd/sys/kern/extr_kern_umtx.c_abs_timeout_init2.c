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
struct abs_timeout {int dummy; } ;
struct _umtx_time {int _flags; int /*<<< orphan*/  _timeout; int /*<<< orphan*/  _clockid; } ;

/* Variables and functions */
 int UMTX_ABSTIME ; 
 int /*<<< orphan*/  abs_timeout_init (struct abs_timeout*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
abs_timeout_init2(struct abs_timeout *timo, const struct _umtx_time *umtxtime)
{

	abs_timeout_init(timo, umtxtime->_clockid,
	    (umtxtime->_flags & UMTX_ABSTIME) != 0, &umtxtime->_timeout);
}