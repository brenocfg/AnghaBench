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
typedef  int /*<<< orphan*/  const_efidp ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Nflag ; 
 int /*<<< orphan*/  efidp_format_device_path (char*,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
devpath_dump(uint8_t *data, size_t datalen)
{
	char buffer[1024];

	efidp_format_device_path(buffer, sizeof(buffer),
	    (const_efidp)data, datalen);
	if (!Nflag)
		printf(": ");
	printf("%s\n", buffer);
}