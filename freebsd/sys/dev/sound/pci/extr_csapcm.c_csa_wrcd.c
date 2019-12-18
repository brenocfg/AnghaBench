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
typedef  int /*<<< orphan*/  u_int32_t ;
struct csa_info {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ BA0_AC97_RESET ; 
 int /*<<< orphan*/  csa_active (struct csa_info*,int) ; 
 int /*<<< orphan*/  csa_writecodec (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csa_wrcd(kobj_t obj, void *devinfo, int regno, u_int32_t data)
{
	struct csa_info *csa = (struct csa_info *)devinfo;

	csa_active(csa, 1);
	csa_writecodec(&csa->res, regno + BA0_AC97_RESET, data);
	csa_active(csa, -1);

	return 0;
}