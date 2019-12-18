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
struct mac {int m_buflen; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAC_MAX_LABEL_BUF_LEN ; 

int
mac_check_structmac_consistent(struct mac *mac)
{

	/* Require that labels have a non-zero length. */
	if (mac->m_buflen > MAC_MAX_LABEL_BUF_LEN ||
	    mac->m_buflen <= sizeof(""))
		return (EINVAL);

	return (0);
}