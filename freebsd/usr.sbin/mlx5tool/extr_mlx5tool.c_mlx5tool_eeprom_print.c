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
struct mlx5_eeprom_get {size_t eeprom_info_out_len; scalar_t__ eeprom_info_buf; scalar_t__ eeprom_info_page_valid; } ;

/* Variables and functions */
 int MLX5_EEPROM_HIGH_PAGE_OFFSET ; 
 int MLX5_EEPROM_PAGE_LENGTH ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
mlx5tool_eeprom_print(struct mlx5_eeprom_get *eeprom_info)
{
	int index_in_row, line_length, row;
	size_t byte_to_write;

	byte_to_write = 0;
	line_length = 16;

	printf("\nOffset\t\tValues\n");
	printf("------\t\t------");
	while (byte_to_write < eeprom_info->eeprom_info_out_len) {
		printf("\n0x%04zX\t\t", byte_to_write);
		for (index_in_row = 0; index_in_row < line_length;
		    index_in_row++) {
			printf("%02X ",
			    ((uint8_t *)eeprom_info->eeprom_info_buf)[
			    byte_to_write]);
			byte_to_write++;
		}
	}

	if (eeprom_info->eeprom_info_page_valid) {
		row = MLX5_EEPROM_HIGH_PAGE_OFFSET;
		printf("\n\nUpper Page 0x03\n");
		printf("\nOffset\t\tValues\n");
		printf("------\t\t------");
		for (row = MLX5_EEPROM_HIGH_PAGE_OFFSET;
		    row < MLX5_EEPROM_PAGE_LENGTH;) {
			printf("\n0x%04X\t\t", row);
			for (index_in_row = 0;
			     index_in_row < line_length;
			     index_in_row++) {
				printf("%02X ",
				    ((uint8_t *)eeprom_info->
				    eeprom_info_buf)[byte_to_write]);
				byte_to_write++;
				row++;
			}
		}
	}
	printf("\n");
}