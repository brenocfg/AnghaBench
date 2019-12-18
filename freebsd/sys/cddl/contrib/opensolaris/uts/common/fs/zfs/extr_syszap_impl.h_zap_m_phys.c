#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* zap_dbuf; } ;
typedef  TYPE_2__ zap_t ;
typedef  int /*<<< orphan*/  mzap_phys_t ;
struct TYPE_4__ {int /*<<< orphan*/ * db_data; } ;

/* Variables and functions */

inline mzap_phys_t *
zap_m_phys(zap_t *zap)
{
	return (zap->zap_dbuf->db_data);
}