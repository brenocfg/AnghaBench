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

/* Variables and functions */
#define  LINUX_SCM_CREDENTIALS 129 
#define  LINUX_SCM_RIGHTS 128 
 int SCM_CREDS ; 
 int SCM_RIGHTS ; 

__attribute__((used)) static int
linux_to_bsd_cmsg_type(int cmsg_type)
{

	switch (cmsg_type) {
	case LINUX_SCM_RIGHTS:
		return (SCM_RIGHTS);
	case LINUX_SCM_CREDENTIALS:
		return (SCM_CREDS);
	}
	return (-1);
}