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
struct pata_macio_priv {int kind; unsigned int** treg; } ;

/* Variables and functions */
#define  controller_heathrow 134 
#define  controller_k2_ata6 133 
#define  controller_kl_ata3 132 
#define  controller_kl_ata4 131 
#define  controller_ohare 130 
#define  controller_sh_ata6 129 
#define  controller_un_ata6 128 

__attribute__((used)) static void pata_macio_default_timings(struct pata_macio_priv *priv)
{
	unsigned int value, value2 = 0;

	switch(priv->kind) {
		case controller_sh_ata6:
			value = 0x0a820c97;
			value2 = 0x00033031;
			break;
		case controller_un_ata6:
		case controller_k2_ata6:
			value = 0x08618a92;
			value2 = 0x00002921;
			break;
		case controller_kl_ata4:
			value = 0x0008438c;
			break;
		case controller_kl_ata3:
			value = 0x00084526;
			break;
		case controller_heathrow:
		case controller_ohare:
		default:
			value = 0x00074526;
			break;
	}
	priv->treg[0][0] = priv->treg[1][0] = value;
	priv->treg[0][1] = priv->treg[1][1] = value2;
}