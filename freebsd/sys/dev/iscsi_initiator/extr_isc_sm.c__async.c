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
typedef  int /*<<< orphan*/  pduq_t ;
struct TYPE_4__ {int /*<<< orphan*/  isc; } ;
typedef  TYPE_1__ isc_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  iscsi_async (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdu_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_async(isc_session_t *sp, pduq_t *pq)
{
     debug_called(8);

     iscsi_async(sp, pq);

     pdu_free(sp->isc, pq);
}