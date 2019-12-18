#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  auth; } ;
struct datalink {TYPE_1__ chap; int /*<<< orphan*/  pap; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_StopTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chap_ReInit (TYPE_1__*) ; 

__attribute__((used)) static void
datalink_AuthReInit(struct datalink *dl)
{
  auth_StopTimer(&dl->pap);
  auth_StopTimer(&dl->chap.auth);
  chap_ReInit(&dl->chap);
}