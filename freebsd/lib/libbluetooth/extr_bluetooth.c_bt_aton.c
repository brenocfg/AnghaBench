#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* b; } ;
typedef  TYPE_1__ bdaddr_t ;

/* Variables and functions */
 int bt_hex_byte (char const*) ; 
 int bt_hex_nibble (char const) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

int
bt_aton(char const *str, bdaddr_t *ba)
{
	int	 i, b;
	char	*end = NULL;

	memset(ba, 0, sizeof(*ba));

	for (i = 5, end = strchr(str, ':');
	     i > 0 && *str != '\0' && end != NULL;
	     i --, str = end + 1, end = strchr(str, ':')) {
		switch (end - str) {
		case 1:
			b = bt_hex_nibble(str[0]);
			break;

		case 2:
			b = bt_hex_byte(str);
			break;

		default:
			b = -1;
			break;
		}
		
		if (b < 0)
			return (0);

		ba->b[i] = b;
	}

	if (i != 0 || end != NULL || *str == 0)
		return (0);

	switch (strlen(str)) {
	case 1:
		b = bt_hex_nibble(str[0]);
		break;

	case 2:
		b = bt_hex_byte(str);
		break;

	default:
		b = -1;
		break;
	}

	if (b < 0)
		return (0);

	ba->b[i] = b;

	return (1);
}