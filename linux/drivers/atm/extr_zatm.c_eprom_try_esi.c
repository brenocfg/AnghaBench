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
struct zatm_dev {int dummy; } ;
struct atm_dev {int /*<<< orphan*/  esi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESI_LEN ; 
 struct zatm_dev* ZATM_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  ZEPROM_ADDR_LEN ; 
 int /*<<< orphan*/  ZEPROM_CMD_LEN ; 
 int ZEPROM_CMD_READ ; 
 int /*<<< orphan*/  ZEPROM_CS ; 
 int ZEPROM_SIZE ; 
 int /*<<< orphan*/  eprom_get_byte (struct zatm_dev*,unsigned char*,unsigned short) ; 
 int /*<<< orphan*/  eprom_put_bits (struct zatm_dev*,int,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  eprom_set (struct zatm_dev*,int /*<<< orphan*/ ,unsigned short) ; 
 int memcmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eprom_try_esi(struct atm_dev *dev, unsigned short cmd, int offset,
			 int swap)
{
	unsigned char buf[ZEPROM_SIZE];
	struct zatm_dev *zatm_dev;
	int i;

	zatm_dev = ZATM_DEV(dev);
	for (i = 0; i < ZEPROM_SIZE; i += 2) {
		eprom_set(zatm_dev,ZEPROM_CS,cmd); /* select EPROM */
		eprom_put_bits(zatm_dev,ZEPROM_CMD_READ,ZEPROM_CMD_LEN,cmd);
		eprom_put_bits(zatm_dev,i >> 1,ZEPROM_ADDR_LEN,cmd);
		eprom_get_byte(zatm_dev,buf+i+swap,cmd);
		eprom_get_byte(zatm_dev,buf+i+1-swap,cmd);
		eprom_set(zatm_dev,0,cmd); /* deselect EPROM */
	}
	memcpy(dev->esi,buf+offset,ESI_LEN);
	return memcmp(dev->esi,"\0\0\0\0\0",ESI_LEN); /* assumes ESI_LEN == 6 */
}