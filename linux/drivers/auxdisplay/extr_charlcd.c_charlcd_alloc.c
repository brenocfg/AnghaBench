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
struct charlcd {int ifwidth; int /*<<< orphan*/  drvdata; int /*<<< orphan*/  hwidth; int /*<<< orphan*/  bwidth; } ;
struct TYPE_2__ {int len; } ;
struct charlcd_priv {int /*<<< orphan*/  drvdata; struct charlcd lcd; TYPE_1__ esc_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_LCD_BWIDTH ; 
 int /*<<< orphan*/  DEFAULT_LCD_HWIDTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct charlcd_priv* kzalloc (int,int /*<<< orphan*/ ) ; 

struct charlcd *charlcd_alloc(unsigned int drvdata_size)
{
	struct charlcd_priv *priv;
	struct charlcd *lcd;

	priv = kzalloc(sizeof(*priv) + drvdata_size, GFP_KERNEL);
	if (!priv)
		return NULL;

	priv->esc_seq.len = -1;

	lcd = &priv->lcd;
	lcd->ifwidth = 8;
	lcd->bwidth = DEFAULT_LCD_BWIDTH;
	lcd->hwidth = DEFAULT_LCD_HWIDTH;
	lcd->drvdata = priv->drvdata;

	return lcd;
}