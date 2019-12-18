#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  nss_name; } ;
struct ipl_parameter_block {TYPE_1__ ccw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (char*,size_t) ; 
 size_t NSS_NAME_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void reipl_get_ascii_nss_name(char *dst,
				     struct ipl_parameter_block *ipb)
{
	memcpy(dst, ipb->ccw.nss_name, NSS_NAME_SIZE);
	EBCASC(dst, NSS_NAME_SIZE);
	dst[NSS_NAME_SIZE] = 0;
}