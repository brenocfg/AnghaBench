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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  RESOURCE_DATA ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  _PNP_ADDRESS ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isapnp_readport ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
isapnp_get_resource_info(uint8_t *buffer, int len)
{
    int		i, j;
    u_char	temp;

    for (i = 0; i < len; i++) {
	outb(_PNP_ADDRESS, STATUS);
	for (j = 0; j < 100; j++) {
	    if ((inb(isapnp_readport)) & 0x1)
		break;
	    delay(1);
	}
	if (j == 100) {
	    printf("PnP device failed to report resource data\n");
	    return(1);
	}
	outb(_PNP_ADDRESS, RESOURCE_DATA);
	temp = inb(isapnp_readport);
	if (buffer != NULL)
	    buffer[i] = temp;
    }
    return(0);
}