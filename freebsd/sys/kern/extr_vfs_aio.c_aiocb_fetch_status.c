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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct aiocb {TYPE_1__ _aiocb_private; } ;

/* Variables and functions */
 long fuword (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
aiocb_fetch_status(struct aiocb *ujob)
{

	return (fuword(&ujob->_aiocb_private.status));
}