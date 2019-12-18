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
typedef  int uint8_t ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (int) ; 

__attribute__((used)) static int  hci_dump_adv(uint8_t *data, int length)
{
	int elemlen;
	int type;
	int i;

	while(length>0){
		elemlen = *data;
		data++;
		length --;
		elemlen--;
		if(length<=0)
			break;
		type = *data;
		data++;
		length --;
		elemlen--;
		if(length<=0)
			break;
		switch(type){
		case 0x1:
			printf("NDflag:%x\n", *data);
			break;
		case 0x9:
			printf("LocalName:");
			for(i = 0; i < MIN(length,elemlen); i++){
				putchar(data[i]);
			}
			printf("\n");
			break;
		default:
			printf("Type%d:", type);
			for(i=0; i < MIN(length,elemlen); i++){
				printf("%02x ",data[i]);
			}
			printf("\n");
			break;
		}
		data += elemlen;
		length -= elemlen;
	}
	return 0;
}