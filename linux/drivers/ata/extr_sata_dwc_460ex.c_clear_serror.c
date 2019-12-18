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
typedef  int /*<<< orphan*/  u32 ;
struct ata_port {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCR_ERROR ; 
 int /*<<< orphan*/  sata_dwc_scr_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sata_dwc_scr_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_serror(struct ata_port *ap)
{
	u32 val;
	sata_dwc_scr_read(&ap->link, SCR_ERROR, &val);
	sata_dwc_scr_write(&ap->link, SCR_ERROR, val);
}