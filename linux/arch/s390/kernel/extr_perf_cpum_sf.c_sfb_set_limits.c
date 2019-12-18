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
struct hws_qsi_info_block {int /*<<< orphan*/  bsdes; int /*<<< orphan*/  dsdes; } ;
typedef  int /*<<< orphan*/  si ;

/* Variables and functions */
 unsigned long CPUM_SF_MAX_SDB ; 
 unsigned long CPUM_SF_MIN_SDB ; 
 int /*<<< orphan*/  CPUM_SF_SDB_DIAG_FACTOR ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hws_qsi_info_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsi (struct hws_qsi_info_block*) ; 

__attribute__((used)) static void sfb_set_limits(unsigned long min, unsigned long max)
{
	struct hws_qsi_info_block si;

	CPUM_SF_MIN_SDB = min;
	CPUM_SF_MAX_SDB = max;

	memset(&si, 0, sizeof(si));
	if (!qsi(&si))
		CPUM_SF_SDB_DIAG_FACTOR = DIV_ROUND_UP(si.dsdes, si.bsdes);
}