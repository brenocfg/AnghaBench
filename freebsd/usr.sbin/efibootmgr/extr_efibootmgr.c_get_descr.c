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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  char efi_char ;

/* Variables and functions */
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int ucs2len (char*) ; 

__attribute__((used)) static char *
get_descr(uint8_t *data)
{
	uint8_t *pos = data;
	efi_char *desc;
	int  len;
	char *buf;
	int i = 0;

	pos += sizeof(uint32_t) + sizeof(uint16_t);
	desc = (efi_char*)(intptr_t)(void *)pos;
	len = ucs2len(desc);
	buf = malloc(len + 1);
	memset(buf, 0, len + 1);
	while (desc[i]) {
		buf[i] = desc[i];
		i++;
	}
	return (char*)buf;
}