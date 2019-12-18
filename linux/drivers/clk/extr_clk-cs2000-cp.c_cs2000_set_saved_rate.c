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
struct cs2000_priv {int /*<<< orphan*/  saved_parent_rate; int /*<<< orphan*/  saved_rate; } ;

/* Variables and functions */
 int __cs2000_set_rate (struct cs2000_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs2000_set_saved_rate(struct cs2000_priv *priv)
{
	int ch = 0; /* it uses ch0 only at this point */

	return __cs2000_set_rate(priv, ch,
				 priv->saved_rate,
				 priv->saved_parent_rate);
}