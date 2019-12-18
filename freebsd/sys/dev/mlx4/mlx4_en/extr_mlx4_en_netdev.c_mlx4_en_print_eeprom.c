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
typedef  int u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void mlx4_en_print_eeprom(u8 *data, __u32 len)
{
	int		i;
	int		j = 0;
	int		row = 0;
	const int	NUM_OF_BYTES = 16;

	printf("\nOffset\t\tValues\n");
	printf("------\t\t------\n");
	while(row < len){
		printf("0x%04x\t\t",row);
		for(i=0; i < NUM_OF_BYTES; i++){
			printf("%02x ", data[j]);
			row++;
			j++;
		}
		printf("\n");
	}
}