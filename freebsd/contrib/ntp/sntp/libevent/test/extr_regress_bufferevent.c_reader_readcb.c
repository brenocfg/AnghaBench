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
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 scalar_t__ bufferevent_getfd (struct bufferevent*) ; 
 int /*<<< orphan*/  n_reads_invoked ; 

__attribute__((used)) static void
reader_readcb(struct bufferevent *bev, void *ctx)
{
	TT_BLATHER(("Read invoked on %d.", (int)bufferevent_getfd(bev)));
	n_reads_invoked++;
}