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
struct TestContext {int dummy; } ;

/* Variables and functions */
 int vale_attach (struct TestContext*) ; 
 int vale_detach (struct TestContext*) ; 

__attribute__((used)) static int
vale_attach_detach(struct TestContext *ctx)
{
	int ret;

	if ((ret = vale_attach(ctx)) != 0) {
		return ret;
	}

	return vale_detach(ctx);
}