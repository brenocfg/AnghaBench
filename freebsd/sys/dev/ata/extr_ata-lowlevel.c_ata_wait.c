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
typedef  int u_int8_t ;
struct ata_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ALTSTAT ; 
 int ATA_DEV (int) ; 
 int /*<<< orphan*/  ATA_DRIVE ; 
 int ATA_D_IBM ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_IDX_OUTB (struct ata_channel*,int /*<<< orphan*/ ,int) ; 
 int ATA_S_BUSY ; 
 int ATA_S_ERROR ; 
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static int
ata_wait(struct ata_channel *ch, int unit, u_int8_t mask)
{
    u_int8_t status;
    int timeout = 0;
    
    DELAY(1);

    /* wait at max 1 second for device to get !BUSY */ 
    while (timeout < 1000000) {
	status = ATA_IDX_INB(ch, ATA_ALTSTAT);

	/* if drive fails status, reselect the drive and try again */
	if (status == 0xff) {
	    ATA_IDX_OUTB(ch, ATA_DRIVE, ATA_D_IBM | ATA_DEV(unit));
	    timeout += 1000;
	    DELAY(1000);
	    continue;
	}

	/* are we done ? */
	if (!(status & ATA_S_BUSY))
	    break;            

	if (timeout > 1000) {
	    timeout += 1000;
	    DELAY(1000);
	}
	else {
	    timeout += 10;
	    DELAY(10);
	}
    }    
    if (timeout >= 1000000)      
	return -2;          
    if (!mask)     
	return (status & ATA_S_ERROR);   

    DELAY(1);
    
    /* wait 50 msec for bits wanted */     
    timeout = 5000;
    while (timeout--) {   
	status = ATA_IDX_INB(ch, ATA_ALTSTAT);
	if ((status & mask) == mask) 
	    return (status & ATA_S_ERROR);            
	DELAY(10);         
    }     
    return -3;      
}