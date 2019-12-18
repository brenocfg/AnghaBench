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
struct knote {scalar_t__ kn_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ msgbuf_getcount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgbuf_lock ; 
 int /*<<< orphan*/  msgbufp ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
logkqread(struct knote *kn, long hint)
{

	mtx_assert(&msgbuf_lock, MA_OWNED);
	kn->kn_data = msgbuf_getcount(msgbufp);
	return (kn->kn_data != 0);
}