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
struct txseginfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  txseginfo_zone ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ertt_mod_init(void)
{

	txseginfo_zone = uma_zcreate("ertt_txseginfo", sizeof(struct txseginfo),
	    NULL, NULL, NULL, NULL, 0, 0);

	return (0);
}