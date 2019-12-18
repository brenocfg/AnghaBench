#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  posted_2; int /*<<< orphan*/  (* wait_cond ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  posted_1; int /*<<< orphan*/  (* signal_cond ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ worker_config ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void worker(void* arg) {
  worker_config* c = arg;
  c->signal_cond(c, &c->posted_1);
  c->wait_cond(c, &c->posted_2);
}