#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* uio_iov; } ;
struct cryptop_data {TYPE_2__ uio; } ;
struct TYPE_3__ {struct cryptop_data* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_XDATA ; 
 int /*<<< orphan*/  free (struct cryptop_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cod_free(struct cryptop_data *cod)
{

	free(cod->uio.uio_iov[0].iov_base, M_XDATA);
	free(cod, M_XDATA);
}