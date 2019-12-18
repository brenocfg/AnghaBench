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
typedef  int u_int32_t ;
struct agg_info {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AGG_RD (struct agg_info*,int /*<<< orphan*/ ,int) ; 
 int CODEC_STAT_MASK ; 
 int /*<<< orphan*/  PORT_CODEC_STAT ; 

__attribute__((used)) static u_int32_t
agg_ac97_init(kobj_t obj, void *sc)
{
	struct agg_info *ess = sc;

	return (AGG_RD(ess, PORT_CODEC_STAT, 1) & CODEC_STAT_MASK)? 0 : 1;
}