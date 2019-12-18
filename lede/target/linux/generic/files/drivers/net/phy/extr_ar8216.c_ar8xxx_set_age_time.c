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
typedef  int u32 ;
struct ar8xxx_priv {int /*<<< orphan*/  arl_age_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8216_ATU_CTRL_AGE_TIME ; 
 int AR8216_ATU_CTRL_AGE_TIME_S ; 
 int ar8xxx_age_time_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_rmw (struct ar8xxx_priv*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
ar8xxx_set_age_time(struct ar8xxx_priv *priv, int reg)
{
	u32 age_time = ar8xxx_age_time_val(priv->arl_age_time);
	ar8xxx_rmw(priv, reg, AR8216_ATU_CTRL_AGE_TIME, age_time << AR8216_ATU_CTRL_AGE_TIME_S);
}