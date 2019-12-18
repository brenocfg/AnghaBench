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
 int LINUX_SCM_CREDENTIALS ; 
 int LINUX_SCM_RIGHTS ; 
 int LINUX_SCM_TIMESTAMP ; 
#define  SCM_CREDS 130 
#define  SCM_RIGHTS 129 
#define  SCM_TIMESTAMP 128 

__attribute__((used)) static int
bsd_to_linux_cmsg_type(int cmsg_type)
{

	switch (cmsg_type) {
	case SCM_RIGHTS:
		return (LINUX_SCM_RIGHTS);
	case SCM_CREDS:
		return (LINUX_SCM_CREDENTIALS);
	case SCM_TIMESTAMP:
		return (LINUX_SCM_TIMESTAMP);
	}
	return (-1);
}