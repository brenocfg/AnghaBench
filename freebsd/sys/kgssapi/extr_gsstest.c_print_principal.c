#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  TYPE_1__* rpc_gss_principal_t ;
struct TYPE_3__ {int len; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_principal(rpc_gss_principal_t principal)
{
	int i, len, n;
	uint8_t *p;

	len = principal->len;
	p = (uint8_t *) principal->name;
	while (len > 0) {
		n = len;
		if (n > 16)
			n = 16;
		for (i = 0; i < n; i++)
			printf("%02x ", p[i]);
		for (; i < 16; i++)
			printf("   ");
		printf("|");
		for (i = 0; i < n; i++)
			printf("%c", isprint(p[i]) ? p[i] : '.');
		printf("|\n");
		len -= n;
		p += n;
	}
}