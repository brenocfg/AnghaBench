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
struct TYPE_3__ {char* bootfs; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 char const* strrchr (char*,char) ; 

const char *
be_nextboot_name(libbe_handle_t *lbh)
{

	if (*lbh->bootfs != '\0')
		return (strrchr(lbh->bootfs, '/') + sizeof(char));
	else
		return (lbh->bootfs);
}