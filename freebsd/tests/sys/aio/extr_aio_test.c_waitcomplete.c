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
struct aiocb {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (struct aiocb*,struct aiocb*) ; 
 int /*<<< orphan*/  aio_waitcomplete (struct aiocb**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
waitcomplete(struct aiocb *aio)
{
	struct aiocb *aiop;
	ssize_t ret;

	ret = aio_waitcomplete(&aiop, NULL);
	ATF_REQUIRE_EQ(aio, aiop);
	return (ret);
}