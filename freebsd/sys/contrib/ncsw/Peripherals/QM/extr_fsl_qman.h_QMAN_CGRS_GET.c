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
typedef  int /*<<< orphan*/  uint8_t ;
struct qman_cgrs {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int QM_MCR_QUERYCONGESTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ int QMAN_CGRS_GET(struct qman_cgrs *c, int num)
{
    return QM_MCR_QUERYCONGESTION(&c->q, (uint8_t)num);
}