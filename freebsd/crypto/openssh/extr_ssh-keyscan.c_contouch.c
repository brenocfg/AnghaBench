#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {TYPE_1__ c_tv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_link ; 
 TYPE_2__* fdcon ; 
 int /*<<< orphan*/  monotime_tv (TYPE_1__*) ; 
 scalar_t__ timeout ; 
 int /*<<< orphan*/  tq ; 

__attribute__((used)) static void
contouch(int s)
{
	TAILQ_REMOVE(&tq, &fdcon[s], c_link);
	monotime_tv(&fdcon[s].c_tv);
	fdcon[s].c_tv.tv_sec += timeout;
	TAILQ_INSERT_TAIL(&tq, &fdcon[s], c_link);
}